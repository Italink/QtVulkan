#ifndef VulkanWindow_h__
#define VulkanWindow_h__

#include <QVulkanWindowRenderer>
#include <vulkan\vulkan.hpp>
class TriangleRenderer: public QVulkanWindowRenderer {
public:
	TriangleRenderer(QVulkanWindow * window);
	void initResources() override;
	void initSwapChainResources() override;
	void releaseSwapChainResources() override;
	void releaseResources() override;
	void startNextFrame() override;
private:
	vk::ShaderModule loadShader(const QString& name);
private:
	QVulkanWindow* window_ = nullptr;

	vk::Buffer singleBuffer_;
	vk::DeviceMemory singleDevMemory_;

	vk::DescriptorBufferInfo vertexBufferInfo_;
	vk::DescriptorBufferInfo indexBufferInfo_;
	vk::DescriptorBufferInfo uniformBufferInfo_[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];


	vk::DescriptorPool descPool_;
	vk::DescriptorSetLayout descSetLayout_;
	vk::DescriptorSet descSet_[QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT];

	vk::PipelineCache piplineCache_;
	vk::PipelineLayout piplineLayout_;
	vk::Pipeline pipline_;
};

class VulkanWindow: public QVulkanWindow{
public:
	QVulkanWindowRenderer* createRenderer() override{ return new TriangleRenderer(this); }
};

#endif // VulkanWindow_h__

