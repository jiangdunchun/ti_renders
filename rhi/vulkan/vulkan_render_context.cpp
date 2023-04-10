#include "vulkan/vulkan_render_context.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "vulkan/vulkan_surface.h"
#include "vulkan/vulkan_render_pass.h"

namespace tigine { namespace rhi {
namespace {
bool checkValidationLayerSupport(const std::vector<const char *> &validation_layers) {
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    std::vector<VkLayerProperties> available_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

    for (auto layer_name : validation_layers) {
        bool layer_found = false;

        for (auto &layer_properties : available_layers) {
            if (strcmp(layer_name, layer_properties.layerName) == 0) {
                layer_found = true;
                break;
            }
        }

        if (!layer_found) return false;
    }

    return true;
}

std::vector<const char *> getRequiredExtensions(bool enable_validation_layers) {
    uint32_t     glfw_extension_count = 0;
    const char **glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    std::vector<const char *> extensions(glfw_extensions, glfw_extensions + glfw_extension_count);

    if (enable_validation_layers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      message_severity,
                                                    VkDebugUtilsMessageTypeFlagsEXT             message_type,
                                                    const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
                                                    void                                       *user_data) {
    std::cerr << "validation layer: " << callback_data->pMessage << std::endl;
    return VK_FALSE;
}

void createDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &o_create_info) {
    o_create_info               = {};
    o_create_info.sType         = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    o_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    o_create_info.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    o_create_info.pfnUserCallback = debugCallback;
}

VkResult createDebugUtilsMessengerEXT(const VkInstance                         &instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT *create_info,
                                      const VkAllocationCallbacks              *allocator,
                                      VkDebugUtilsMessengerEXT                 *debug_messenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, create_info, allocator, debug_messenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

bool checkDeviceExtensionSupport(const VkPhysicalDevice &physical_device, const std::vector<const char *> &device_extensions) {
    uint32_t extension_count;
    vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, nullptr);

    std::vector<VkExtensionProperties> available_extensions(extension_count);
    vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extension_count, available_extensions.data());

    std::set<std::string> required_extensions(device_extensions.begin(), device_extensions.end());

    for (auto &extension : available_extensions) {
        required_extensions.erase(extension.extensionName);
    }

    return required_extensions.empty();
}

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR        capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   present_modes;
};

SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice &physical_device, const VkSurfaceKHR &surface) {
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &details.capabilities);

    uint32_t format_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, nullptr);

    if (format_count != 0) {
        details.formats.resize(format_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, details.formats.data());
    }

    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &present_mode_count, nullptr);

    if (present_mode_count != 0) {
        details.present_modes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &present_mode_count, details.present_modes.data());
    }

    return details;
}

struct QueueFamilyIndices {
    int graphics_family = -1;
    int present_family  = -1;

    bool isComplete() { return graphics_family >= 0 && present_family >= 0; }
};

QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &physical_device, const VkSurfaceKHR &surface) {
    QueueFamilyIndices indices;

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

    int i = 0;
    for (auto &queue_family : queue_families) {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphics_family = i;
        }

        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &present_support);

        if (present_support) {
            indices.present_family = i;
        }

        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

bool isDeviceSuitable(const VkPhysicalDevice &physical_device, const VkSurfaceKHR &surface, const std::vector<const char *> &device_extensions) {
    QueueFamilyIndices indices = findQueueFamilies(physical_device, surface);

    bool extensions_supported = checkDeviceExtensionSupport(physical_device, device_extensions);

    bool swapchain_adequate = false;
    if (extensions_supported) {
        SwapChainSupportDetails swapchain_support = querySwapChainSupport(physical_device, surface);
        swapchain_adequate                        = !swapchain_support.formats.empty() && !swapchain_support.present_modes.empty();
    }

    return indices.isComplete() && extensions_supported && swapchain_adequate;
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &available_formats) {
    for (const auto &available_format : available_formats) {
        if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB && available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return available_format;
        }
    }

    return available_formats[0];
}

VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &available_present_modes) {
    for (const auto &available_present_mode : available_present_modes) {
        if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return available_present_mode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window) {
    if (capabilities.currentExtent.width != UINT32_MAX) {
        return capabilities.currentExtent;
    } else {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actual_extent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};

        actual_extent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actual_extent.width));
        actual_extent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actual_extent.height));

        return actual_extent;
    }
}




void createWindow(
    const Extent2D &resolution,
    GLFWwindow *&o_window) {
    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    o_window = glfwCreateWindow(resolution.width, resolution.height, "", NULL, NULL);
    if (!o_window) {
        RHI_VULKAN_THROW("can't create vulkan window");
    }
}

void createInstance(
    bool enable_validation_layers, const std::vector<const char *> &validation_layers,
    VkInstance &o_instance) {
    if (enable_validation_layers && !checkValidationLayerSupport(validation_layers)) {
        RHI_VULKAN_THROW("validation layers requested, but not available!");
    }

    VkApplicationInfo app_info {};
    app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName   = "ti_render";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName        = "ti_render";
    app_info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion         = VK_API_VERSION_1_0;

    VkInstanceCreateInfo create_info {};
    create_info.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    std::vector<const char *> extensions = getRequiredExtensions(enable_validation_layers);
    create_info.enabledExtensionCount    = static_cast<uint32_t>(extensions.size());
    create_info.ppEnabledExtensionNames  = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
    if (enable_validation_layers) {
        create_info.enabledLayerCount   = static_cast<uint32_t>(validation_layers.size());
        create_info.ppEnabledLayerNames = validation_layers.data();
        createDebugMessengerCreateInfo(debug_create_info);
        create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debug_create_info;
    } else {
        create_info.enabledLayerCount = 0;
        create_info.pNext = nullptr;
    }

    RHI_VULKAN_THROW_IF_FAILD(vkCreateInstance(&create_info, nullptr, &o_instance),
        "failed to create instance!");
}

void setupDebugMessenger(
    VkInstance &instance, bool enable_validation_layers,
    VkDebugUtilsMessengerEXT &o_debug_messenger) {
    if (!enable_validation_layers) return;

    VkDebugUtilsMessengerCreateInfoEXT create_info;
    createDebugMessengerCreateInfo(create_info);
    RHI_VULKAN_THROW_IF_FAILD(createDebugUtilsMessengerEXT(instance, &create_info, nullptr, &o_debug_messenger),
        "failed to set up debug messenger!");
}

void createSurface(
    VkInstance &instance, GLFWwindow *&window, 
    VkSurfaceKHR &o_surface) {
    RHI_VULKAN_THROW_IF_FAILD(glfwCreateWindowSurface(instance, window, nullptr, &o_surface),
        "failed to create window surface!");
}

void pickPhysicalDevice(
    VkInstance &instance, VkSurfaceKHR &surface, const std::vector<const char *> &device_extensions,
    VkPhysicalDevice &o_physical_device) {
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

    if (device_count == 0) {
        RHI_VULKAN_THROW("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

    for (const auto &device : devices) {
        if (isDeviceSuitable(device, surface, device_extensions)) {
            o_physical_device = device;
            break;
        }
    }

    if (o_physical_device == VK_NULL_HANDLE) {
        RHI_VULKAN_THROW("failed to find a suitable GPU!");
    }
}

void createLogicalDevice(
    VkPhysicalDevice &physical_device, VkSurfaceKHR &surface, const std::vector<const char *> &device_extensions, const bool &enable_validation_layers, const std::vector<const char *> &validation_layers,
    VkDevice &o_device, VkQueue  &o_graphics_queue, VkQueue &o_present_queue,uint32_t &o_graphics_family) {
    QueueFamilyIndices indices = findQueueFamilies(physical_device, surface);

    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    std::set<uint32_t>                   queue_families = {uint32_t(indices.graphics_family), uint32_t(indices.present_family)};

    float queue_priority = 1.0f;
    for (int queue_family : queue_families) {
        VkDeviceQueueCreateInfo queue_create_info {};
        queue_create_info.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex = queue_family;
        queue_create_info.queueCount       = 1;
        queue_create_info.pQueuePriorities = &queue_priority;
        queue_create_infos.push_back(queue_create_info);
    }

    VkPhysicalDeviceFeatures device_features {};

    VkDeviceCreateInfo device_create_info {};
    device_create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.queueCreateInfoCount    = static_cast<uint32_t>(queue_create_infos.size());
    device_create_info.pQueueCreateInfos       = queue_create_infos.data();
    device_create_info.pEnabledFeatures        = &device_features;
    device_create_info.enabledExtensionCount   = static_cast<uint32_t>(device_extensions.size());
    device_create_info.ppEnabledExtensionNames = device_extensions.data();

    if (enable_validation_layers) {
        device_create_info.enabledLayerCount   = static_cast<uint32_t>(validation_layers.size());
        device_create_info.ppEnabledLayerNames = validation_layers.data();
    } else {
        device_create_info.enabledLayerCount = 0;
    }

    RHI_VULKAN_THROW_IF_FAILD(vkCreateDevice(physical_device, &device_create_info, nullptr, &o_device),
        "failed to create logical device!");

    vkGetDeviceQueue(o_device, indices.graphics_family, 0, &o_graphics_queue);
    vkGetDeviceQueue(o_device, indices.present_family, 0, &o_present_queue);
    o_graphics_family = indices.graphics_family;
}

void createSwapChain(
    VkPhysicalDevice &physical_device, VkDevice &device, GLFWwindow *&window, VkSurfaceKHR &surface,
    VkSwapchainKHR  &o_swapchain, VkFormat &o_swapchain_image_format, VkExtent2D &o_swapchain_extent, std::vector<VkImage> &o_swapchain_images) {
    SwapChainSupportDetails swapchain_support = querySwapChainSupport(physical_device, surface);
    VkSurfaceFormatKHR      surface_format    = chooseSwapSurfaceFormat(swapchain_support.formats);
    VkPresentModeKHR        present_mode      = chooseSwapPresentMode(swapchain_support.present_modes);
    VkExtent2D              extent            = chooseSwapExtent(swapchain_support.capabilities, window);
    uint32_t                image_count       = swapchain_support.capabilities.minImageCount + 1;
    if (swapchain_support.capabilities.maxImageCount > 0 && image_count > swapchain_support.capabilities.maxImageCount) {
        image_count = swapchain_support.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR swapchain_info {};
    swapchain_info.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_info.surface          = surface;
    swapchain_info.minImageCount    = image_count;
    swapchain_info.imageFormat      = surface_format.format;
    swapchain_info.imageColorSpace  = surface_format.colorSpace;
    swapchain_info.imageExtent      = extent;
    swapchain_info.imageArrayLayers = 1;
    swapchain_info.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices                = findQueueFamilies(physical_device, surface);
    uint32_t           queue_family_indices[] = {indices.graphics_family, indices.present_family};
    if (indices.graphics_family != indices.present_family) {
        swapchain_info.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
        swapchain_info.queueFamilyIndexCount = 2;
        swapchain_info.pQueueFamilyIndices   = queue_family_indices;
    } else {
        swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    swapchain_info.preTransform   = swapchain_support.capabilities.currentTransform;
    swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_info.presentMode    = present_mode;
    swapchain_info.clipped        = VK_TRUE;

    RHI_VULKAN_THROW_IF_FAILD(vkCreateSwapchainKHR(device, &swapchain_info, nullptr, &o_swapchain),
        "failed to create swap chain!");

    o_swapchain_image_format = surface_format.format;
    o_swapchain_extent       = extent;

    vkGetSwapchainImagesKHR(device, o_swapchain, &image_count, nullptr);
    o_swapchain_images.resize(image_count);
    vkGetSwapchainImagesKHR(device, o_swapchain, &image_count, o_swapchain_images.data());
}

void createSwapchainImageViews(
    VkDevice &device, VkFormat &swapchain_image_format, std::vector<VkImage> &swapchain_images,
    std::vector<VkImageView> &o_swapchain_image_views) {
    o_swapchain_image_views.resize(swapchain_images.size());
    for (size_t i = 0; i < swapchain_images.size(); i++) {
        VkImageViewCreateInfo image_view_info {};
        image_view_info.sType                           = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        image_view_info.image                           = swapchain_images[i];
        image_view_info.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
        image_view_info.format                          = swapchain_image_format;
        image_view_info.components.r                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.components.g                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.components.b                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.components.a                    = VK_COMPONENT_SWIZZLE_IDENTITY;
        image_view_info.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
        image_view_info.subresourceRange.baseMipLevel   = 0;
        image_view_info.subresourceRange.levelCount     = 1;
        image_view_info.subresourceRange.baseArrayLayer = 0;
        image_view_info.subresourceRange.layerCount     = 1;

        RHI_VULKAN_THROW_IF_FAILD(vkCreateImageView(device, &image_view_info, nullptr, &o_swapchain_image_views[i]),
            "failed to create image views!");
    }
}

void createSwapchainFrameBuffers(
    VkDevice &device, VkRenderPass &render_pass, VkExtent2D &swapchain_extent, std::vector<VkImageView> &swapchain_image_views,
    std::vector<VkFramebuffer> &o_swapchain_frame_buffers) {
    o_swapchain_frame_buffers.resize(swapchain_image_views.size());
    for (size_t i = 0; i < swapchain_image_views.size(); i++) {
        VkImageView attachments[] = {swapchain_image_views[i]};

        VkFramebufferCreateInfo framebuffer_info {};
        framebuffer_info.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebuffer_info.renderPass      = render_pass;
        framebuffer_info.attachmentCount = 1;
        framebuffer_info.pAttachments    = attachments;
        framebuffer_info.width           = swapchain_extent.width;
        framebuffer_info.height          = swapchain_extent.height;
        framebuffer_info.layers          = 1;

        RHI_VULKAN_THROW_IF_FAILD(vkCreateFramebuffer(device, &framebuffer_info, nullptr, &o_swapchain_frame_buffers[i]),
            "failed to create frame buffer!");
    }
}

void createSyncObjects(
    VkDevice &device, 
     VkSemaphore &o_image_available_semaphore, VkSemaphore &o_render_finished_semaphore) {
    VkSemaphoreCreateInfo semaphore_info {};
    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    RHI_VULKAN_THROW_IF_FAILD(vkCreateSemaphore(device, &semaphore_info, nullptr, &o_image_available_semaphore),
        "failed to create synchronization objects for a frame!");
    RHI_VULKAN_THROW_IF_FAILD(vkCreateSemaphore(device, &semaphore_info, nullptr, &o_render_finished_semaphore),
        "failed to create synchronization objects for a frame!");
}
} // namespace

VulkanRenderContext::VulkanRenderContext(const RenderContextDesc &desc, VulkanContextInfo &o_context) {
#ifdef NDEBUG
    const bool enable_validation_layers = false;
#else
    const bool enable_validation_layers = true;
#endif
    const std::vector<const char *> validation_layers = {"VK_LAYER_KHRONOS_validation"};
    const std::vector<const char *> device_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    
    GLFWwindow *window = nullptr;
    createWindow(
        desc.resolution,
        window);
    VulkanSurface *vulkan_surface = new VulkanSurface(window);
    surface_                      = vulkan_surface;

    createInstance(
        enable_validation_layers, validation_layers,
        vk_instance_);

    setupDebugMessenger(
        vk_instance_, enable_validation_layers,
        vk_debug_messenger_);

    createSurface(
        vk_instance_, vulkan_surface->getWindow(),
        vk_surface_KHR_);

    pickPhysicalDevice(vk_instance_, vk_surface_KHR_, device_extensions,
        vk_physicl_device_);

    createLogicalDevice(
        vk_physicl_device_, vk_surface_KHR_, device_extensions, enable_validation_layers, validation_layers,
        vk_device_, vk_graphics_queue_, vk_present_queue_, vk_graphics_family_);

    o_context = {&vk_physicl_device_, &vk_device_, &vk_graphics_queue_, vk_graphics_family_};
    
    createSwapChain(
        vk_physicl_device_, vk_device_, vulkan_surface->getWindow(), vk_surface_KHR_,
        vk_swapchain_, vk_swapchain_image_format_, vk_swapchain_extent_, vk_swapchain_images_);

    createSwapchainImageViews(
        vk_device_, vk_swapchain_image_format_, vk_swapchain_images_, 
        vk_swapchain_image_views_);

    RenderPassDesc render_pass_desc;
    render_pass_desc.color_attachments.resize(1);
    // @FIXME
    // only support the BGRA8UNorm_sRGB now(same with the format of swapchain imageview)
    render_pass_desc.color_attachments[0].format = DataFormat::BGRA8UNorm_sRGB;
    render_pass_desc.color_attachments[0].load   = AttachmentLoadOp::Clear;
    render_pass_desc.color_attachments[0].store  = AttachmentStoreOp::Store;
    render_pass_desc.samples             = desc.samples;
    VulkanRenderPass *vulkan_render_pass = new VulkanRenderPass(o_context, render_pass_desc);
    render_pass_                         = vulkan_render_pass;

    createSwapchainFrameBuffers(
        vk_device_, *vulkan_render_pass->getVkRenderPass(), vk_swapchain_extent_, vk_swapchain_image_views_, 
        vk_swapchain_frame_buffers_);

    createSyncObjects(
        vk_device_, 
        vk_image_available_semaphore_, vk_render_finished_semaphore_);

    acquireNextPresentImage();
}

VulkanRenderContext::~VulkanRenderContext() {
    delete surface_;
    delete render_pass_;
    glfwTerminate();
}

void VulkanRenderContext::present() {
    VkSemaphore          wait_semaphorse[]   = {vk_image_available_semaphore_};
    VkPipelineStageFlags wait_stages[]       = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    VkSemaphore          signal_semaphores[] = {vk_render_finished_semaphore_};

    VkSubmitInfo submit_info {};
    submit_info.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.pNext                = nullptr;
    submit_info.waitSemaphoreCount   = 1;
    submit_info.pWaitSemaphores      = wait_semaphorse;
    submit_info.pWaitDstStageMask    = wait_stages;
    submit_info.commandBufferCount   = 0;
    submit_info.pCommandBuffers      = nullptr;
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores    = signal_semaphores;
    RHI_VULKAN_THROW_IF_FAILD(vkQueueSubmit(vk_graphics_queue_, 1, &submit_info, VK_NULL_HANDLE),
        "failed to submit semaphore to Vulkan graphics queue!");

    VkSwapchainKHR swap_chains[] = {vk_swapchain_};

    VkPresentInfoKHR present_info {};
    present_info.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present_info.pNext              = nullptr;
    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores    = signal_semaphores;
    present_info.swapchainCount     = 1;
    present_info.pSwapchains        = swap_chains;
    present_info.pImageIndices      = &present_image_index_;
    present_info.pResults           = nullptr;
    RHI_VULKAN_THROW_IF_FAILD(vkQueuePresentKHR(vk_present_queue_, &present_info),
        "failed to present Vulkan graphics queue!");

    acquireNextPresentImage();
}

void VulkanRenderContext::acquireNextPresentImage() {
    vkAcquireNextImageKHR(vk_device_, vk_swapchain_, UINT64_MAX, vk_image_available_semaphore_, VK_NULL_HANDLE, &present_image_index_);
}
}} // namespace tigine::rhi
