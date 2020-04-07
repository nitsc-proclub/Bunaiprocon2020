#pragma once
#include "Shared.h"
#include"imgui_markdown.h"

class MarkdownViewWindow :
	public IEvent
{
private:
	int imagesIdx;
	std::string markdownStr;
	String parentPath;
	String fileName;
public:
	struct ImageData
	{
		String assetName;
		bool isValid = false;
		bool isChached = false;
		std::shared_ptr<Texture> chacedTexture;
	};
	std::shared_ptr<Texture> imageIcon = std::shared_ptr<Texture>(new Texture(Icon(0xf03e, 30)));
	std::shared_ptr<Texture> imageFileIcon = std::shared_ptr<Texture>(new Texture(Icon(0xf1c5, 30)));
	ImGui::MarkdownConfig mdConfig;
	Array<ImageData> images;
	void OpenFile(String path);
	MarkdownViewWindow(String path);
	bool RunEvent(double per);
};

