import clang.cindex #pip install libclang
import argparse

# parser = argparse.ArgumentParser()
# parser.add_argument('-input', required=True, default="", help='input header file')
# parser.add_argument('-proj_dir', default="./", help='project directory')
# args = parser.parse_args()
# print(args.input)
# print(args.proj_dir)

def traverse(node, depth):
    if node.kind is clang.cindex.CursorKind.NAMESPACE and str(node.get_usr()).__contains__("reflection_test"):
        for n in node.get_children():
            traverse_reflect(n, depth + 1)
    else:        
        for n in node.get_children():
            traverse(n, depth + 1)

def traverse_reflect(node, depth):
    print("%s%s %s" %("|   " * depth, str(node.kind), node.get_usr()))
    for n in node.get_children():
        traverse_reflect(n, depth + 1)

clang.cindex.Config.set_library_path("./")
index = clang.cindex.Index.create()
parser = index.parse("E:/study/ti_renders/tests/tigine.reflection.test/test.h", ["-ObjC++"])
cursor = parser.cursor
traverse(cursor, 0)