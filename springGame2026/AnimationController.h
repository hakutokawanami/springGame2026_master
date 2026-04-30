#pragma once
#include<string>
#include<map>
class AnimationController
{
public:
	//モデルハンドルを受け取る
	AnimationController(int modelHandle);
	//更新
	void Update();
	/// <summary>
	// アニメーション再生
	/// </summary>
	/// <param name="name">アニメーション名</param>
	/// <param name="loop">ループするかどうか</param>
	/// <param name="blendTime">ブレンドにかかる時間</param>
	void Play(const std::string& name, bool loop = true, float blendTime = 15.0f);
	/// <summary>
	/// アニメーション登録
	/// </summary>
	/// <param name="name">アニメーション名</param>
	/// <param name="animIndex">アニメーション番号</param>
	void AddAnimation(const std::string& name, int animIndex);
	/// <summary>
	/// ループしないアニメーションが終わったかどうか
	/// </summary>
	bool IsEnd() {return m_isEnd ; }

private:
	//モデルハンドル
	int m_modelHandle;

	//アニメーション名とアニメーション番号
	std::map<std::string, int>m_animTable;
	//---------------------
	// 現在のアニメーション
	//---------------------
	
	//アニメーション番号
	int m_currentAnim;
	//アタッチ番号
	int m_currentAttachNo;
	//再生時間
	float m_currentTime;
	//ループするかどうか
	bool m_isLoop;
	//アニメーションが終わったかどうか
	bool m_isEnd;

	//---------------------
	//前のアニメーション(ブレンドに使う)
	//---------------------

	//アニメーション番号
	int m_prevAnim;
	//アタッチ番号
	int m_prevAttachNo;
	//再生時間
	float m_prevTime;

	//---------------------
	//ブレンド制御
	//---------------------

	//ブレンドにかける時間
	float m_blendTime;
	//経過時間
	float m_blendTimer;
};

