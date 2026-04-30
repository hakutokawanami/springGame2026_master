#pragma once
#include<array>
enum class FontType
{
	UI,
	Title,
	Count
};

class FontManager
{
public:
	//初期化
	static void Init();

	//解放
	static void End();

	//フォントハンドルの取得
	static int GetFontHandle(FontType type);

	//中央寄せDraw
	static void DrawCenterString(int centerX, int y, const wchar_t* text, int color, FontType type);
	//フェード付き
	static void DrawCenterFadeString(int centerX, int y, const wchar_t* text, int color, FontType type);
	//枠をつける
	static void DrawOutLineString(int x, int y, const wchar_t* text, int textColor, int outlineColor, int FontType);
	//文字の間隔を調整する
	static int GetStringWidthSpacing(const wchar_t* text,FontType type,int spacing);
	//文字の間隔を反映した描画
	static void DrawStringSpacing(int x, int y, const wchar_t* text, int color, int font,int spacing);
private:
	//フォントハンドルの配列
	static std::array<int, (int)FontType::Count>m_fonts;

	static float m_time;
};

