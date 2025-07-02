#include <VulkanApp.hpp>

VulkanApp::VulkanApp()
	: _window(nullptr), _vk(VK_NULL_HANDLE), _vk_device(VK_NULL_HANDLE),
	  _vk_physical(VK_NULL_HANDLE), _vk_graphics_queue(VK_NULL_HANDLE)
{
	LOG_DEBUG("VulkanApp created");
}

VulkanApp::~VulkanApp()
{
	if (_vk_device)
		vkDestroyDevice(_vk_device, nullptr);
	if (_vk)
		vkDestroyInstance(_vk, nullptr);
	if (_window) {
		glfwDestroyWindow(_window);
		glfwTerminate();
	}
	LOG_DEBUG("VulkanApp destroyed");
}

void VulkanApp::initWindow()
{
	if (!glfwInit())
		throw WindowInitException();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	_window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, nullptr, nullptr);
	if (!_window) {
		glfwTerminate();
		throw WindowInitException();
	}
	LOG_OK("Window initialized successfully");
}

void VulkanApp::initVulkan()
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = WIN_TITLE;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

	if (vkCreateInstance(&createInfo, nullptr, &_vk) != VK_SUCCESS)
		throw VulkanInitException();
	LOG_OK("Vulkan instance created successfully");
}

void VulkanApp::loop() {
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(_window, true);
	}
}

int VulkanApp::run() {
	try {
		initWindow();
		initVulkan();
	} catch (const std::exception& e) {
		LOG_ERR("Exception: %s", e.what());
		return EXIT_FAILURE;
	}
	loop();
	return EXIT_SUCCESS;
}
