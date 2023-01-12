#include <iostream>

#include "serializer_test.hpp"

void serializer_test() { 
	serializer_test_1 serializer_test_1_var(1,2,3);
    serializer_test_2 serializer_test_2_var(1.0f, 2.0, false, "serializer_test_2");
    serializer_test_3 serializer_test_3_var(serializer_test_1_var, serializer_test_2_var);

	json serializer_test_3_var_json = meta::serializer::to_json(serializer_test_3_var);
    std::cout << "serializer_test_3_var:" << serializer_test_3_var_json.dump() << std::endl;

	serializer_test_3 *serializer_test_3_copy_var = new serializer_test_3();
    meta::serializer::from_json(serializer_test_3_var_json, serializer_test_3_copy_var);
    std::cout << "serializer_test_3_copy_var.serializer_test_1_var_:" 
              << meta::serializer::to_json(serializer_test_3_copy_var->serializer_test_1_var_).dump() << std::endl;
    std::cout << "serializer_test_3_copy_var.serializer_test_2_var_:"
              << meta::serializer::to_json(serializer_test_3_copy_var->serializer_test_2_var_).dump() << std::endl;
}

int main(int, char **) { 
	serializer_test();
}