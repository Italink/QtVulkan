#include <QGuiApplication>
#include <QVulkanInstance>
#include "VulkanWindow.h"
#include <QLoggingCategory>
Q_LOGGING_CATEGORY(lcVk, "qt.vulkan")

int main(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);

	static vk::DynamicLoader  dynamicLoader;
	PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = dynamicLoader.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
	VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);
	QVulkanInstance instance;
	if (!instance.create())
		qFatal("Failed to create Vulkan instance: %d", instance.errorCode());
	VULKAN_HPP_DEFAULT_DISPATCHER.init(instance.vkInstance());

	QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));
	instance.setLayers({ "VK_LAYER_KHRONOS_validation" });
	VulkanWindow vkWindow;
	vkWindow.setVulkanInstance(&instance);
	vkWindow.resize(1024, 768);
	vkWindow.show();
	return app.exec();
}

