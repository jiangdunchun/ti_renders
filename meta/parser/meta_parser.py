import clang.cindex #pip install libclang
import argparse

# parser = argparse.ArgumentParser()
# parser.add_argument('-input', required=True, default="", help='input header file')
# parser.add_argument('-proj_dir', default="./", help='project directory')
# args = parser.parse_args()
# print(args.input)
# print(args.proj_dir)

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

type_fields = {}
type_methods = {}

def traverse(node, p_namespace):
    if node.kind == clang.cindex.CursorKind.NAMESPACE:
        c_namespace = p_namespace + node.spelling + '::'
        for child in node.get_children():
            traverse(child, c_namespace)
    elif node.kind == clang.cindex.CursorKind.CLASS_DECL:
        is_meta, is_white_list = check_meta_properties(node)
        if is_meta:
            fields, methods = get_fields_and_methods(node, is_white_list)
            if len(fields) != 0:
                type_fields[p_namespace + node.spelling] = fields
            if len(methods) != 0:
                type_methods[p_namespace + node.spelling] = methods
    else:
        for child in node.get_children():
            traverse(child, p_namespace)

clang.cindex.Config.set_library_path("./")
index = clang.cindex.Index.create()
parser = index.parse("../../tests/meta.test/meta_test.hpp", ["-ObjC++", "-D__META_PARSER__"])
cursor = parser.cursor
traverse(cursor, '')
print("type_fields:" + str(type_fields))
print("type_methods:" + str(type_methods))
