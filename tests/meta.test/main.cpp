#include <iostream>

#include "serializer_test.hpp"

void serializer_test() { 
	SerializerTest1 serializer_test_1_var(1, 2, 3);
    SerializerTest2 serializer_test_2_var(1.0f, 2.0, false, "serializer_test_2");
    SerializerTest3 serializer_test_3_var(serializer_test_1_var, serializer_test_2_var);

	json serializer_test_3_var_json = meta::Serializer::toJson(serializer_test_3_var);
    std::cout << "serializer_test_3_var:" << serializer_test_3_var_json.dump() << std::endl;

	SerializerTest3 *serializer_test_3_copy_var = new SerializerTest3();
    meta::Serializer::fromJson(serializer_test_3_var_json, serializer_test_3_copy_var);
    std::cout << "serializer_test_3_copy_var.serializer_test_1_var_:" 
              << meta::Serializer::toJson(serializer_test_3_copy_var->serializer_test_1_var_).dump() << std::endl;
    std::cout << "serializer_test_3_copy_var.serializer_test_2_var_:"
              << meta::Serializer::toJson(serializer_test_3_copy_var->serializer_test_2_var_).dump() << std::endl;
}

#include "reflector_test.hpp"

void reflector_test() { 
    // regist
    ReflectorTest1::makeReflectable();


    meta::TypeMeta reflector_test_1_t_meta = meta::Reflector::getType("ReflectorTest1");
    meta::FieldMeta reflector_test_1_char_var_f_meta = reflector_test_1_t_meta.getField("char_var_");
    meta::FieldMeta reflector_test_1_int_var_f_meta = reflector_test_1_t_meta.getField("int_var_");
    meta::FieldMeta reflector_test_1_unsigned_int_var_f_meta = reflector_test_1_t_meta.getField("unsigned_int_var_");

    ReflectorTest1 reflector_test_1_var;
    reflector_test_1_char_var_f_meta.set(reflector_test_1_var, 'a');
    reflector_test_1_int_var_f_meta.set(reflector_test_1_var, 2);
    reflector_test_1_unsigned_int_var_f_meta.set(reflector_test_1_var, 3);

    std::cout << "reflector_test_1_var.char_var_:" << reflector_test_1_var.char_var_ << std::endl
              << "reflector_test_1_var.int_var_:" << reflector_test_1_var.int_var_ << std::endl
              << "reflector_test_1_var.unsigned_int_var_:" << reflector_test_1_var.unsigned_int_var_ << std::endl;

    reflector_test_1_var.char_var_ = 'b';
    reflector_test_1_var.int_var_  = 3;
    reflector_test_1_var.unsigned_int_var_ = 4;

    std::cout << "reflector_test_1_char_var_f_meta.get<char>(reflector_test_1_var):" 
              << reflector_test_1_char_var_f_meta.get<char>(reflector_test_1_var) << std::endl
              << "reflector_test_1_int_var_f_meta.get<int>(reflector_test_1_var):" 
              << reflector_test_1_int_var_f_meta.get<int>(reflector_test_1_var) << std::endl
              << "reflector_test_1_unsigned_int_var_f_meta.get<unsigned int>(reflector_test_1_var):"
              << reflector_test_1_unsigned_int_var_f_meta.get<unsigned int>(reflector_test_1_var) << std::endl;
}

int main(int, char **) { 
	serializer_test();
    reflector_test();
}