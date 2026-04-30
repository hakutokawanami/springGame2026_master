#include "FontManager.h"
#include<DxLib.h>

namespace
{
	//黒枠の太さの値
	constexpr int kOutLineOffset = 2;
	//文字の間隔
	constexpr int kSpacing = 10;

	constexpr int kUISize = 64;
	constexpr int kTitleSize = 128;

	constexpr int kFadeInterval = 30;
	constexpr float kFadeSpeed = 0.08f;
}

std::array<int, (int)FontType::Count> FontManager::m_fonts;
float FontManager::m_time;

void FontManager::Init()
{
	//フォントの追加
	AddFontResourceEx(L"data/donguri.ttf", FR_PRIVATE, NULL);

	//UI
	m_fonts[(int)FontType::UI] =
		CreateFontToHandle(L"x10y12pxDonguriDuel", kUISize, 5);

	m_fonts[(int)FontType::Title] = 
		CreateFontToHandle(L"x10y12pxDonguriDuel", kTitleSize, 5);

	m_time = 0.0f;
}

void FontManager::End()
{
	//フォントハンドルの削除
	for(int i = 0; i < (int)FontType::Count; i++)
	{
		DeleteFontToHandle(m_fonts[i]);
	}

	//フォントの削除
	RemoveFontResourceEx(L"data/donguri.ttf", FR_PRIVATE, NULL);
}

int FontManager::GetFontHandle(FontType type)
{
	return m_fonts[(int)type];
}

void FontManager::DrawCenterString(int centerX, int y, const wchar_t* text, int color, FontType type)
{
	int font = FontManager::GetFontHandle(type);
	//横幅取得
	int width = GetStringWidthSpacing(text, type, kSpacing);
	//x座標計算
	int x = centerX - width / 2;
	
	DrawStringSpacing(x, y, text, color,font,kSpacing);
}

void FontManager::DrawCenterFadeString(int centerX, int y, const wchar_t* text, int color, FontType type)
{
	int font = FontManager::GetFontHandle(type);
	//横幅取得
	int width = GetStringWidthSpacing(text, type, kSpacing);
	//x座標計算
	int x = centerX - width / 2;
	//フェードを進める
	m_time += kFadeSpeed;
	//sin(-1～1)
	float value = sinf(m_time);
	//0～1に変換
	value = (value + 1.0f) * 0.5f;
	//フェード処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 + 135 * value);
	DrawStringSpacing(x, y, text, color, font, kSpacing);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FontManager::DrawOutLineString(int x, int y, const wchar_t* text, int textColor, int outlineColor, int fontType)
{
	//外枠（8方向）
	DrawStringToHandle(x - kOutLineOffset, y,				   text, outlineColor, fontType);
	DrawStringToHandle(x + kOutLineOffset, y,				   text, outlineColor, fontType);
	DrawStringToHandle(x,				   y - kOutLineOffset, text, outlineColor, fontType);
	DrawStringToHandle(x,				   y + kOutLineOffset, text, outlineColor, fontType);
	DrawStringToHandle(x - kOutLineOffset, y - kOutLineOffset, text, outlineColor, fontType);
	DrawStringToHandle(x + kOutLineOffset, y - kOutLineOffset, text, outlineColor, fontType);
	DrawStringToHandle(x - kOutLineOffset, y + kOutLineOffset, text, outlineColor, fontType);
	DrawStringToHandle(x + kOutLineOffset, y + kOutLineOffset, text, outlineColor, fontType);

	// 本体
	DrawStringToHandle(x, y, text, textColor,fontType);
}

int FontManager::GetStringWidthSpacing(const wchar_t* text, FontType type, int spacing)
{
	int fontHandle = GetFontHandle(type);

	int width = 0;
	//一文字ずつ取り出す
	for (int i = 0; text[i] != L'\0'; i++)
	{
		//文字列に直す
		wchar_t ch[2] = { text[i],L'\0' };
		//文字幅を取得
		if (type == FontType::UI)
		{
			width += GetDrawStringWidthToHandle(
				ch,
				1,
				fontHandle);
		}
		else if (type == FontType::Title)
		{
			width += GetDrawStringWidthToHandle(
				ch,
				1,
				fontHandle);
		}
		
		//文字の間隔を開ける
		if (text[i + 1] != L'\0')
		{
			width += spacing;
		}
	}
	//最終的な横幅を返す
	return width;
}

void FontManager::DrawStringSpacing(int x, int y, const wchar_t* text, int color, int font, int spacing)
{
	int drawX = x;
	//一文字ずつ取り出す
	for (int i = 0; text[i] != L'\0'; i++)
	{
		//文字列に直す
		wchar_t ch[2] = { text[i],L'\0' };
		//一文字描画
		DrawOutLineString(drawX, y, ch, color,0x000000, font);
		//文字幅取得
		int width = GetDrawStringWidthToHandle(ch, 1, font);
		//文字の間隔を開ける
		drawX += width + spacing;
	}
}
