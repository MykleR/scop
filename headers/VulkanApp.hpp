#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <debug.hpp>
#include <utils.hpp>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WIN_TITLE "Vulkan APP"

class VulkanApp
{
FIELD(GLFWwindow*, _window)
FIELD(VkInstance, _vk)
FIELD(VkDevice, _vk_device)
FIELD(VkPhysicalDevice, _vk_physical)
FIELD(VkQueue, _vk_graphics_queue)

EXCEPTION(VulkanInitException, "Vulkan initialization failed");
EXCEPTION(WindowInitException, "Window initialization failed");
EXCEPTION(VulkanShaderException, "Vulkan shader compilation failed");

public:
	VulkanApp();
	~VulkanApp();

	int run();

private:
	void initWindow();
	void initVulkan();
	void loop();
};
