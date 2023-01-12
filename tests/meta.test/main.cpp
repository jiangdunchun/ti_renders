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

int main(int, char **) { 
	serializer_test();
}