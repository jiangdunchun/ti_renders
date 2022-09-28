#include "vulkan/vulkan_render_context.h"

#include <stdexcept>
#include <vector>
#include <iostream>

namespace tigine { namespace graphic {
namespace {
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
                                                    VkDebugUtilsMessageTypeFlagsEXT             messageType,
                                                    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                    void                                       *pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

void setExtensions(VkInstanceCreateInfo &create_info) {
    uint32_t     glfw_extension_count = 0;
    const char **glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    std::vector<const char *> extensions(glfw_extensions, glfw_extensions + glfw_extension_count);
#ifndef NDEBUG 
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif // NDEBUG 

    create_info.enabledExtensionCount   = static_cast<TUInt>(extensions.size());
    create_info.ppEnabledExtensionNames = extensions.data();
}

void setDebuger(VkInstanceCreateInfo& create_info) { 
#ifndef NDEBUG
    const std::vector<const char *>    validation_layers = {"VK_LAYER_KHRONOS_validation"};
    create_info.enabledLayerCount   = static_cast<uint32_t>(validation_layers.size());
    create_info.ppEnabledLayerNames = validation_layers.data();

    VkDebugUtilsMessengerCreateInfoEXT debug_create_info {};
    debug_create_info.sType    = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT 
                                        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                                        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT 
                                    | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                                    | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_create_info.pfnUserCallback = debugCallback;
    create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debug_create_info;
#else
    create_info.enabledLayerCount = 0;
    create_info.pNext = nullptr;
#endif // NDEBUG
}

void createInstance(VkInstance &instance) {
    VkApplicationInfo app_info {};
    app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName   = "graphic";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName        = "tigine";
    app_info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion         = VK_API_VERSION_1_0;

    VkInstanceCreateInfo create_info {};
    create_info.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    setExtensions(create_info);
    setDebuger(create_info);
    
    if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS) { throw std::runtime_error("failed to create instance!"); }
}
} // namespace

VulkanRenderContext::VulkanRenderContext(const RenderContextDescriptor &desc) {
    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window_ = glfwCreateWindow(desc.width, desc.height, "", NULL, NULL);
    if (!window_) throw std::runtime_error("can't create vulkan window");

    glfwMakeContextCurrent(window_);
    createInstance(instance);

    surface_     = new VulkanSurface(window_);
    render_pass_ = nullptr;
}

VulkanRenderContext::~VulkanRenderContext() {
    if (window_) glfwDestroyWindow(window_);
    delete surface_;
    delete render_pass_;
    glfwTerminate();
}
}} // namespace tigine::graphic
