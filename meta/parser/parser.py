import clang.cindex #pip install libclang
import argparse

# parser = argparse.ArgumentParser()
# parser.add_argument('-input', required=True, default="", help='input header file')
# parser.add_argument('-proj_dir', default="./", help='project directory')
# args = parser.parse_args()
# print(args.input)
# print(args.proj_dir)

def check_meta_property(node):
    is_reflectible = False
    is_serializable = False
    for child in node.get_children():
        if child.kind == clang.cindex.CursorKind.ANNOTATE_ATTR:
            attributes = child.displayname.replace(' ', '').split(';')
            if len(attributes) > 0 and attributes[0] == 'META':
                for attribute in attributes:
                    if attribute == 'REFLECTIBLE':
                        is_reflectible = True
                    elif attribute == 'SERIALIZABLE':
                        is_serializable = True
    return is_reflectible, is_serializable

def traverse(node, p_namespace):
    if node.kind == clang.cindex.CursorKind.NAMESPACE:
        c_namespace = node.displayname + '::' + p_namespace
        for child in node.get_children():
            traverse(child, c_namespace)
    elif node.kind == clang.cindex.CursorKind.CLASS_DECL:
        is_reflectible, is_serializable = check_meta_property(node)
        if is_reflectible:
            print(p_namespace + node.displayname + " is_reflectible")
        if is_serializable:
            print(p_namespace + node.displayname + " is_serializable")
    else:
        for child in node.get_children():
            traverse(child, p_namespace)

clang.cindex.Config.set_library_path("./")
index = clang.cindex.Index.create()
parser = index.parse("../../tests/meta.test/meta_test.hpp", ["-ObjC++"])
cursor = parser.cursor
traverse(cursor, '')