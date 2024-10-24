import clang.cindex #pip install libclang
import argparse




def check_meta_properties(node):
    is_meta = False
    is_white_list = False
    for child in node.get_children():
        if child.kind == clang.cindex.CursorKind.ANNOTATE_ATTR:
            attributes = child.spelling.replace(' ', '').split(';')
            if len(attributes) > 0 and attributes[0] == 'META':
                is_meta = True
                for attribute in attributes:
                    if attribute == 'WHITE_LIST':
                        is_white_list = True
            
    return is_meta, is_white_list

def is_meta_field_or_method(t_meta):
    for child in t_meta.get_children():
        if child.kind == clang.cindex.CursorKind.ANNOTATE_ATTR:
            attributes = child.spelling.replace(' ', '').split(';')
            if len(attributes) > 0 and attributes[0] == 'META':
                return True
    return False

def get_fields_and_methods(t_meta, is_white_list):
    fields = []
    methods = []
    for child in t_meta.get_children():
        if child.kind == clang.cindex.CursorKind.FIELD_DECL and child.access_specifier.name == 'PUBLIC':
            if not is_white_list:
                fields.append(child.spelling)
            else:
                if is_meta_field_or_method(child):
                    fields.append(child.spelling)
        elif child.kind == clang.cindex.CursorKind.CXX_METHOD and child.access_specifier.name == 'PUBLIC':
            if not is_white_list:
                methods.append(child.spelling)
            else:
                if is_meta_field_or_method(child):
                    methods.append(child.spelling)
    return fields, methods

def traverse(node, p_namespace, meta_tree):
    if node.kind == clang.cindex.CursorKind.NAMESPACE:
        if p_namespace == '':
            c_namespace = node.spelling
        else:
            c_namespace = p_namespace + '::' + node.spelling
        for child in node.get_children():
            traverse(child, c_namespace, meta_tree)
    elif node.kind == clang.cindex.CursorKind.CLASS_DECL:
        is_meta, is_white_list = check_meta_properties(node)
        if is_meta:
            fields, methods = get_fields_and_methods(node, is_white_list)
            if len(fields) != 0 or len(methods) != 0:
                meta_type = {}
                meta_type['namespace'] = p_namespace
                meta_type['type'] = node.spelling
                meta_type['fields'] = fields
                meta_type['methods'] = methods
                meta_tree.append(meta_type)
    else:
        for child in node.get_children():
            traverse(child, p_namespace, meta_tree)


print('*******************meta parser pre-building start*******************')

parser = argparse.ArgumentParser()
parser.add_argument('-f', required=True, default="", help='head files')
parser.add_argument('-gh', required=True, default="", help='generated head file')
parser.add_argument('-gc', required=True, default="", help='generated source file')
parser.add_argument('-i', required=True, default="", help='include path')
args = parser.parse_args()




def create_json_function_def(meta_type):
    json_function_template = '''template<>
json meta::Serializer::toJson($[type_name] &instance);
template<>
void meta::Serializer::fromJson(const json &json_context, $[type_name] &instance);'''
    type_name_key = '$[type_name]'

    type_name = ('' if meta_type['namespace'] == '' else (meta_type['namespace'] + '::')) + meta_type['type']
    return json_function_template.replace(type_name_key, type_name)

def write_head_file(gereted_head_file, meta_tree):
    include_file_template = '#include "$[include_file]"'
    include_file_key = '$[include_file]'
    def create_head_file_def(gereted_head_file):
        words, pre_str = [], ''
        for c in gereted_head_file:
            if ord(c) >= ord('a') and ord(c) <= ord('z'):
                pre_str += chr(ord(c) - ord('a') + ord('A'))
            elif (ord(c) >= ord('A') and ord(c) <= ord('Z')) or (ord(c) >= ord('0') and ord(c) <= ord('1')):
                pre_str += c
            else:
                if pre_str != '':
                    words.append(pre_str)
                    pre_str = ''
        if pre_str != '':
            words.append(pre_str)
        head_file_def = words[0]
        for word in words[1:]:
            head_file_def += '_' + word
        return '__' + head_file_def + '__'

    with open(gereted_head_file, 'w') as o_file:
        head_file_def = create_head_file_def(gereted_head_file)
        o_file.write('#ifndef ' + head_file_def + '\n') 
        o_file.write('#define ' + head_file_def + '\n') 
        o_file.write('#include <meta.h>')
        o_file.write('\n\n')

        for head_file in meta_tree.keys():
            o_file.write(include_file_template.replace(include_file_key, head_file))
            o_file.write('\n')
        o_file.write('\n')

        for head_file in meta_tree.keys():
            meta_types = meta_tree[head_file]
            for meta_type in meta_types:
                o_file.write(create_json_function_def(meta_type))
                o_file.write('\n\n')
        o_file.write('#endif')

def create_json_function_impl(meta_type):
    json_impl_template = '''template<>
json meta::Serializer::toJson($[type_name] &instance) {
json::object ret;
$[to_json_items]return ret;
}
template<>
void meta::Serializer::fromJson(const json &json_context, $[type_name] &instance) {
$[from_json_items]}'''
    to_json_item_template = 'ret["$[field_name]"] = toJson(instance.$[field_name]);'
    from_json_item_template = 'fromJson(json_context["$[field_name]"], instance.$[field_name]);'
    type_name_key = '$[type_name]'
    to_json_items_key = '$[to_json_items]'
    from_json_items_key = '$[from_json_items]'
    field_name_key = '$[field_name]'

    to_json_items, from_json_items = '', ''
    for field in meta_type['fields']:
        to_json_items += to_json_item_template.replace(field_name_key, field)
        to_json_items += '\n'
        from_json_items += from_json_item_template.replace(field_name_key, field)
        from_json_items += '\n'

    json_impl = json_impl_template.replace(to_json_items_key, to_json_items)
    json_impl = json_impl.replace(from_json_items_key, from_json_items)
    type_name = ('' if meta_type['namespace'] == '' else (meta_type['namespace'] + '::')) + meta_type['type']
    return json_impl.replace(type_name_key, type_name)

def create_regist_all_function_impl(meta_tree):
    regist_all_template = '''void meta::Reflector::registAll() {$[regist_impl]}'''
    regist_type_template = 'meta::Reflector::registType<$[type_name]>("$[type_name]")'
    regist_field_template = '.addField("$[field_name]", &$[type_name]::$[field_name])'
    regist_method_template = '.addMethod("$[method_name]", &$[type_name]::$[method_name])'
    regist_impl_key = '$[regist_impl]'
    type_name_key = '$[type_name]'
    field_name_key = '$[field_name]'
    method_name_key = '$[method_name]'

    regist_impl = ''
    for head_file in meta_tree.keys():
            meta_types = meta_tree[head_file]
            for meta_type in meta_types:
                
                regist_type_impl = '\n'
                regist_type_impl += regist_type_template
                for field in meta_type['fields']:
                    regist_type_impl += '\n'
                    regist_type_impl += regist_field_template.replace(field_name_key, field)
                for method in meta_type['methods']:
                    regist_type_impl += '\n'
                    regist_type_impl += regist_method_template.replace(method_name_key, method)
                type_name = ('' if meta_type['namespace'] == '' else (meta_type['namespace'] + '::')) + meta_type['type']
                regist_impl += regist_type_impl.replace(type_name_key, type_name)
                regist_impl += ';\n'
    return regist_all_template.replace(regist_impl_key, regist_impl)

def write_cpp_file(gereted_cpp_file, gereted_head_file, meta_tree):
    include_file_template = '#include "$[include_file]"'
    include_file_key = '$[include_file]'

    with open(gereted_cpp_file, 'w') as o_file:
        o_file.write(include_file_template.replace(include_file_key, gereted_head_file))
        o_file.write('\n\n')

        for head_file in meta_tree.keys():
            meta_types = meta_tree[head_file]
            for meta_type in meta_types:
                o_file.write(create_json_function_impl(meta_type))
                o_file.write('\n\n')

        o_file.write(create_regist_all_function_impl(meta_tree))



index = clang.cindex.Index.create()
head_files = args.f.split(';')
meta_tree = {}
for head_file in head_files:
    parser = index.parse(head_file, ["-ObjC++", "-D__META_PARSER__", '-I'+args.i])
    cursor = parser.cursor
    file_meta = []
    traverse(cursor, '', file_meta)
    meta_tree[head_file] = file_meta
print("meta_tree:" + str(meta_tree))

write_head_file(args.gh, meta_tree)
write_cpp_file(args.gc, args.gh, meta_tree)

print('******************meta parser pre-building success******************')