#include <iostream>

#include "meta_test.hpp"

void serializer_test() { 
    std::cout << "serializer test----->" << std::endl;

	MetaTest1 test_1_var(1, 2, 3);
    MetaTest2 test_2_var(1.0f, 2.0, false, "serializer_test_2");
    MetaTest3 test_3_var(test_1_var, test_2_var);

	json test_3_var_json = meta::Serializer::toJson(test_3_var);
    std::cout << "test_3_var:" << test_3_var_json.dump() << std::endl;

	MetaTest3 *test_3_copy_var = new MetaTest3();
    meta::Serializer::fromJson(test_3_var_json, test_3_copy_var);
    std::cout << "test_3_copy_var.test_1_var:" 
              << meta::Serializer::toJson(test_3_copy_var->test_1_var).dump() << std::endl;
    std::cout << "test_3_copy_var.test_2_var:" 
              << meta::Serializer::toJson(test_3_copy_var->test_2_var).dump() << std::endl;
}


void reflector_test() { 
    std::cout << "reflector test----->" << std::endl;
    
    meta::TypeMeta test_1_t_meta = meta::Reflector::getType("MetaTest1");
    meta::FieldMeta test_1_char_var_f_meta = test_1_t_meta.getField("char_var");
    meta::FieldMeta test_1_int_var_f_meta  = test_1_t_meta.getField("int_var");

    meta::TypeMeta test_3_t_meta = meta::Reflector::getType("MetaTest3");
    meta::FieldMeta test_3_test_2_var_f_meta = test_3_t_meta.getField("test_2_var");
    meta::MethodMeta test_3_get_m_meta = test_3_t_meta.getMethod("get");
    meta::MethodMeta test_3_plusandset_m_meta = test_3_t_meta.getMethod("plusandset");

    MetaTest3 test_3_var;

    test_1_char_var_f_meta.set(test_3_var.test_1_var, 'a');
    test_1_int_var_f_meta.set(test_3_var.test_1_var, 2);
    MetaTest2 test_2_var_0(1.0f, 2, true, "test_2_var_0");
    test_3_test_2_var_f_meta.set(test_3_var, test_2_var_0);

    std::cout << "test_3_var.test_1_var.char_var:" << test_3_var.test_1_var.char_var << std::endl
              << "test_3_var.test_1_var.int_var:" << test_3_var.test_1_var.int_var << std::endl
              << "test_3_var.test_2_var.float_var:" << test_3_var.test_2_var.float_var << std::endl
              << "test_3_var.test_2_var.double_var:" << test_3_var.test_2_var.double_var << std::endl
              << "test_3_var.test_2_var.bool_var:" << test_3_var.test_2_var.bool_var << std::endl
              << "test_3_var.test_2_var.string_var:" << test_3_var.test_2_var.string_var << std::endl;

    test_3_var.test_1_var.char_var = 'b';
    test_3_var.test_1_var.int_var = 3;

    std::cout << "test_1_char_var_f_meta.get<char>(test_3_var.test_1_var):" 
              << test_1_char_var_f_meta.get<char>(test_3_var.test_1_var) << std::endl
              << "test_1_int_var_f_meta.get<int>(test_3_var.test_1_var):" 
              << test_1_int_var_f_meta.get<int>(test_3_var.test_1_var) << std::endl;

    test_3_plusandset_m_meta.invoke(test_3_var, char('a'));
    test_3_plusandset_m_meta.invoke(test_3_var, char(2));
    std::cout << "test_3_get_m_meta.invoke<char>(test_3_var):" 
              << test_3_get_m_meta.invoke<char>(test_3_var) << std::endl;
}

int main(int, char **) { 
    /* regist code for all reflectible classes*/
    /*start---------->*/
    meta::Reflector::registAll();
    /*<----------end*/

	serializer_test();
    reflector_test();
}