#include "MarkdownViewWindow.h"

static MarkdownViewWindow* _this;
static int imageIdx;
static String openFilePath = U"";

void LinkCallback(ImGui::MarkdownLinkCallbackData data_)
{
	String url = Unicode::Widen(std::string(data_.link, data_.linkLength));
	//if (!data_.isImage)
	{
		if (FileSystem::Extension(url).lowercase() == U"md")
		{
			openFilePath = url;
		}
		else
		{
			System::LaunchBrowser(url);
		}
	}
}

ImGui::MarkdownImageData ImageCallback_Load(ImGui::MarkdownLinkCallbackData data_)
{
	int idx = imageIdx++;
	String link = Unicode::Widen(std::string(data_.link, data_.linkLength));
	String name = U"Md:{}:{}"_fmt(_this, idx);
	bool valid = TextureAsset::Register(name, link, AssetParameter::LoadAsync());

	MarkdownViewWindow::ImageData data;
	data.assetName = name;
	data.isValid = valid;
	_this->images.push_back(data);

	ImGui::MarkdownImageData imageData;
	imageData.isValid = false;
	return imageData;
}

ImGui::MarkdownImageData ImageCallback(ImGui::MarkdownLinkCallbackData data_)
{
	int idx = imageIdx++;
	auto data = &(_this->images[idx]);
	ImGui::MarkdownImageData imageData;
	imageData.isValid = false;
	if (data->isValid)
	{
		if (data->isChached)
		{
			imageData.user_texture_id = GetImTextureID(data->chacedTexture);
			imageData.size = ImVec2(data->chacedTexture->width(), data->chacedTexture->height());
			imageData.isValid = true;
		}
		else
		{
			if (TextureAsset::IsReady(data->assetName))
			{
				auto texture = TextureAsset(data->assetName);
				if (texture.isEmpty())
				{
					data->isValid = false;
				}
				else
				{
					data->chacedTexture = std::shared_ptr<Texture>(new Texture(texture));
					data->isChached = true;
					imageData.user_texture_id = GetImTextureID(data->chacedTexture);
					imageData.size = ImVec2(data->chacedTexture->width(), data->chacedTexture->height());
					imageData.isValid = true;
				}
				TextureAsset::Unregister(data->assetName);
			}
			else
			{
				imageData.user_texture_id = GetImTextureID(_this->imageIcon);
				imageData.size = ImVec2(_this->imageIcon->width(), _this->imageIcon->height());
				imageData.isValid = true;
			}
		}
	}
	else
	{
		imageData.user_texture_id = GetImTextureID(_this->imageFileIcon);
		imageData.size = ImVec2(_this->imageFileIcon->width(), _this->imageFileIcon->height());
		imageData.useLinkCallback = true;
		imageData.isValid = true;
	}
	return imageData;
}

void MarkdownViewWindow::OpenFile(String path)
{
	String lastCd = FileSystem::CurrentDirectory();
	FileSystem::ChangeCurrentDirectory(parentPath);
	for(auto image : images)
	{
		if (image.isValid && !image.isChached)
		{
			//読み込み中のファイルを登録解除
			TextureAsset::Unregister(image.assetName);
		}
	}
	images.clear();
	TextReader reader(path);
	if (reader.isOpened())
	{
		markdownStr = reader.readAll().toUTF8();
		reader.close();
		parentPath = FileSystem::ParentPath(path);
	}
	else
	{
		markdownStr = U"ファイル {} が見つかりません"_fmt(path).toUTF8();
		parentPath = FileSystem::InitialDirectory();
	}
	fileName = FileSystem::FileName(path);
	mdConfig = ImGui::MarkdownConfig{ LinkCallback, ImageCallback_Load, "", { { NULL, true }, { NULL, true }, { NULL, true } } };
	FileSystem::ChangeCurrentDirectory(lastCd);
}

MarkdownViewWindow::MarkdownViewWindow(String path)
{
	OpenFile(path);
}

bool MarkdownViewWindow::RunEvent(double per)
{
	bool cont = true;
	_this = this;
	imageIdx = 0;
	String lastCd = FileSystem::CurrentDirectory();
	FileSystem::ChangeCurrentDirectory(parentPath);
	ImGui::SetNextWindowPos(ImVec2(20, 20));
	ImGui::SetNextWindowSize(ImVec2(Scene::Width() - 40, Scene::Height() - 40));
	ImGui::Begin(U"MarkdownViewer - {}##{}"_fmt(fileName,this).narrow().c_str(), &cont, ImGuiWindowFlags_NoMove);
	ImGui::Markdown(markdownStr.c_str(), markdownStr.length(), mdConfig);
	mdConfig.imageCallback = ImageCallback;
	ImGui::End();
	FileSystem::ChangeCurrentDirectory(lastCd);
	if (openFilePath.length() > 0)
	{
		OpenFile(openFilePath);
		openFilePath = U"";
	}
	return cont;
}