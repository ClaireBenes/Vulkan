#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
using std::vector;
#include <set>
using std::set;
#include <array>
using std::array;

#include "VulkanUtilities.h"

class VulkanRenderer
{
public:
#ifdef NDEBUG
	static const bool enableValidationLayers = false;
#else
	static const bool enableValidationLayers = true;
#endif
	static const vector<const char*> validationLayers;

public:
	struct
	{
		vk::PhysicalDevice physicalDevice;
		vk::Device logicalDevice;
	} mainDevice;

public:
	VulkanRenderer();
	~VulkanRenderer();

	int init(GLFWwindow* windowP);
	void draw();
	void clean();


private:
	GLFWwindow* window;

	vk::Instance instance;
	vk::Queue graphicsQueue;

	vk::SurfaceKHR surface;
	vk::Queue presentationQueue;

	vk::SwapchainKHR swapchain;
	vk::Format swapchainImageFormat;
	vk::Extent2D swapchainExtent;
	vector<SwapchainImage> swapchainImages;

	vk::PipelineLayout pipelineLayout;
	vk::RenderPass renderPass;

	VkDebugUtilsMessengerEXT debugMessenger;

private:
	void createInstance();
	bool checkInstanceExtensionSupport(const vector<const char*>& checkExtensions);

	void getPhysicalDevice();
	bool checkDeviceSuitable(vk::PhysicalDevice device);
	QueueFamilyIndices getQueueFamilies(vk::PhysicalDevice device);

	void createLogicalDevice();

	bool checkValidationLayerSupport();
	vector<const char*> getRequiredExtensions();

	void setupDebugMessenger();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	vk::SurfaceKHR createSurface();

	bool checkDeviceExtensionSupport(vk::PhysicalDevice device);

	SwapchainDetails getSwapchainDetails(vk::PhysicalDevice device);
	void createSwapchain();

	vk::SurfaceFormatKHR chooseBestSurfaceFormat(const vector<vk::SurfaceFormatKHR>& formats);
	vk::PresentModeKHR chooseBestPresentationMode(const vector<vk::PresentModeKHR>& presentationModes);
	vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);

	vk::ImageView createImageView(vk::Image image, vk::Format format, vk::ImageAspectFlagBits aspectFlags);

	void createGraphicsPipeline();
	vk::ShaderModule createShaderModule(const vector<char>& code);

	void createRenderPass();
};

