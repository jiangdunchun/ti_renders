import clang.cindex #pip install libclang
import argparse

# parser = argparse.ArgumentParser()
# parser.add_argument('-f', required=True, default="", help='head files')
# parser.add_argument('-g', required=True, default="", help='generated file')
# parser.add_argument('-i', required=True, default="", help='include path')
# args = parser.parse_args()

def check_meta_properties(node):
    is_meta = False
    is_white_list = False
    for child in node.get_children():
        # print(str(child.kind) + child.get_usr())
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

meta_type_list = []

def traverse(node, p_namespace):
    if node.kind == clang.cindex.CursorKind.NAMESPACE:
        if p_namespace == '':
            c_namespace = node.spelling
        else:
            c_namespace = p_namespace + '::' + node.spelling
        for child in node.get_children():
            traverse(child, c_namespace)
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
                meta_type_list.append(meta_type)
    else:
        for child in node.get_children():
            traverse(child, p_namespace)

clang.cindex.Config.set_library_path("./")
index = clang.cindex.Index.create()
parser = index.parse("../../tests/meta.test/meta_test.hpp", ["-ObjC++", "-D__META_PARSER__", '-I../'])
cursor = parser.cursor
traverse(cursor, '')
print("meta_type_list:" + str(meta_type_list))
