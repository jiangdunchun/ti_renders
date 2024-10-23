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
                meta_type['file'] = node.location.file.name
                meta_type['namespace'] = p_namespace
                meta_type['type'] = node.spelling
                meta_type['fields'] = fields
                meta_type['methods'] = methods
                meta_tree.append(meta_type)
    else:
        for child in node.get_children():
            traverse(child, p_namespace, meta_tree)



parser = argparse.ArgumentParser()
parser.add_argument('-f', required=True, default="", help='head files')
parser.add_argument('-gh', required=True, default="", help='generated head file')
parser.add_argument('-gc', required=True, default="", help='generated source file')
parser.add_argument('-i', required=True, default="", help='include path')
args = parser.parse_args()


def create_json_function_definition():
    return

def create_head_file_content():
    return


json_template = '''
template<>
json meta::Serializer::toJson($[type_name] &instance) {
json::object ret;$[to_json_items]
return ret;
}
template<>
void meta::Serializer::fromJson(const json &json_context, $[type_name] &instance) {$[from_json_items]
}
'''
to_json_item_template = '''
ret["$[field_name]"] = toJson(instance.$[field_name]);'''
from_json_item_template = '''
fromJson(json_context["$[field_name]"], instance.$[field_name]);'''
type_name_key = '$[type_name]'
to_json_items_key = '$[to_json_items]'
from_json_items_key = '$[from_json_items]'
field_name_key = '$[field_name]'
method_name_key = '$[method_name]'
reflector_template = '''
void meta::Reflector::registAll() {$[reflect_entity]
}'''
reflect_entity_key = '$[reflect_entity]'
reflector_type_template = '''
meta::Reflector::registType<$[type_name]>("$[type_name]")'''
reflector_field_template = '''
.addField("$[field_name]", &$[type_name]::$[field_name])'''
reflector_method_template = '''
.addMethod("$[method_name]", &$[type_name]::$[method_name])'''


#clang.cindex.Config.set_library_path("./")
index = clang.cindex.Index.create()
head_files = args.f.split(';')
meta_tree = []
for head_file in head_files:
    print('meta paser->', head_file)
    parser = index.parse(head_file, ["-ObjC++", "-D__META_PARSER__", '-I'+args.i])
    cursor = parser.cursor
    traverse(cursor, '', meta_tree)
    print("meta_tree:" + str(meta_tree))
with open(args.gc, 'w') as generated_file:
    generated_file.write('#include <meta.h>\n\n')
    #generated_file.write(str(meta_tree))
    for type_ in meta_tree:
        generated_file.write('#include \"'+ type_['file'] + '\"\n')
        type_name = ('' if type_['namespace'] == '' else (type_['namespace'] + '::')) + type_['type']
        json_str = json_template.replace(type_name_key, type_name)
        to_json_items, from_json_items = '', ''
        for field in type_['fields']:
            to_json_items += to_json_item_template.replace(field_name_key, field)
            from_json_items += from_json_item_template.replace(field_name_key, field)
        json_str = json_str.replace(to_json_items_key, to_json_items)
        json_str = json_str.replace(from_json_items_key, from_json_items)
        generated_file.write(json_str)
    
    reflector_str = ''
    for type_ in meta_tree:
        type_name = ('' if type_['namespace'] == '' else (type_['namespace'] + '::')) + type_['type']
        reflector_str += reflector_type_template.replace(type_name_key, type_name)
        for field in type_['fields']:
            reflector_field_str = reflector_field_template.replace(type_name_key, type_name)
            reflector_field_str = reflector_field_str.replace(field_name_key, field)
            reflector_str += reflector_field_str
        for method in type_['methods']:
            reflector_method_str = reflector_method_template.replace(type_name_key, type_name)
            reflector_method_str = reflector_method_str.replace(method_name_key, method)
            reflector_str += reflector_method_str
        reflector_str += ';'

    reflector_entity = reflector_template.replace(reflect_entity_key, reflector_str)
    generated_file.write(reflector_entity)
