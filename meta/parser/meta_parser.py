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
    is_reflectible = False
    is_serializable = False
    for child in node.get_children():
        # print(str(child.kind) + child.get_usr())
        if child.kind == clang.cindex.CursorKind.ANNOTATE_ATTR:
            attributes = child.displayname.replace(' ', '').split(';')
            if len(attributes) > 0 and attributes[0] == 'META':
                is_meta = True
                for attribute in attributes:
                    if attribute == 'WHITE_LIST':
                        is_white_list = True
        elif child.kind == clang.cindex.CursorKind.FRIEND_DECL:
            for friend_class in child.get_children():
                if friend_class.displayname == 'class meta::Serializer':
                    is_serializable = True
        elif child.kind == clang.cindex.CursorKind.CXX_METHOD and child.access_specifier.name == 'PUBLIC' and child.is_static_method() and child.displayname == 'makeReflectible()':
            is_reflectible = True
            
    return is_meta, is_white_list, is_reflectible, is_serializable

def traverse(node, p_namespace):
    if node.kind == clang.cindex.CursorKind.NAMESPACE:
        c_namespace = p_namespace + node.displayname + '::'
        for child in node.get_children():
            traverse(child, c_namespace)
    elif node.kind == clang.cindex.CursorKind.CLASS_DECL:
        is_meta, is_white_list, is_reflectible, is_serializable = check_meta_properties(node)
        if is_meta:
            print(p_namespace + node.displayname + " is_white:" + str(is_white_list) + " is_reflectible:" + str(is_reflectible) + " is_serializable:" + str(is_serializable))
    else:
        for child in node.get_children():
            traverse(child, p_namespace)

clang.cindex.Config.set_library_path("./")
index = clang.cindex.Index.create()
parser = index.parse("../../tests/meta.test/meta_test.hpp", ["-ObjC++"])
cursor = parser.cursor
traverse(cursor, '')