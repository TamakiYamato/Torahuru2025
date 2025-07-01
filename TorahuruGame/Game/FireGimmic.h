#pragma once
#include "MakeEffect.h"
class Loading;
class Game;
class Player;
class FireTriggerFloor;

/// <summary>
/// 火炎放射クラス
/// </summary>
class FireGimmic :public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FireGimmic();

	/// <summary>
	/// 火炎放射の位置を設定
	/// </summary>
	void SetPosition(const Vector3& position)
	{
		m_firePos = position;
	}

	/// <summary>
	/// 火炎放射の大きさの設定
	/// </summary>
	void SetScale(const Vector3& scale)
	{
		m_fireScl = scale;
	}

	/// <summary>
	/// 火炎放射の向きの設定
	/// </summary>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

private:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~FireGimmic();

	/// <summary>
	/// スタート
	/// </summary>
	bool Start();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);

	/// <summary>
	/// 炎の当たり判定の作成
	/// </summary>
	void CreateFireCollision();

	/// <summary>
	/// 火炎放射の再生
	/// </summary>
	void Fire();

	/// <summary>
	/// 火炎放射の停止
	/// </summary>
	void IntervalCollision();

	/// <summary>
	/// 効果音の再生
	/// </summary>
	void PlaySE();

	/// <summary>
	/// 当たり判定の有効・無効を確認するフラグを確認
	/// </summary>
	void CheckFireFlag(bool isMoveFire);

	/// <summary>
	/// 火炎放射が再生されているかフラグで確認
	/// </summary>
	/// <param name="flag"></param>
	void SetMoveFlag(const bool& flag)
	{
		m_moveFlag = flag;
	}

	/// <summary>
	/// エフェクトの再生処理
	/// </summary>
	EffectEmitter* PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

	/// <summary>
	/// 火炎放射の状態を列挙型で確認
	/// </summary>
	enum Status
	{
		enStatus_Idle,	// 待機
		enStatus_Fire,	// 放射中
	};

	Status m_status = enStatus_Idle;		//火炎放射が発射してるか停止してるかのステータス
	EffectEmitter* m_fire = nullptr;		//1つ目の火炎放射
	EffectEmitter* m_fireSecond = nullptr;	//2つ目の火炎放射
	SoundSource* m_se;						//火炎放射の効果音
	Player* m_player = nullptr;
	Game* m_game = nullptr;

	Quaternion m_rotation;
	Quaternion m_fireRot_North;	//火炎放射の向き：北側
	Quaternion m_fireRot_South;	//火炎放射の向き：南側
	Quaternion m_fireRot_East;	//火炎放射の向き：東側
	Quaternion m_fireRot_West;	//火炎放射の向き：西側
	CollisionObject* m_fireCollision;			//1つ目の火炎放射の当たり判定の大きさ
	CollisionObject* m_fireSecondCollision;		//2つ目の火炎放射の当たり判定の大きさ

	Vector3	m_firePos = Vector3::Zero;		 //1つ目の火炎放射の位置
	Vector3 m_fireSecondPos = Vector3::Zero; //2つ目の火炎放射の位置
	Vector3 m_fireScl = Vector3::Zero;		 //1つ目の火炎放射の大きさ
	Vector3 m_fireSecondScl = Vector3::Zero; //2つ目の火炎放射の大きさ

	bool m_moveFlag = true;			//動かしたかどうかのフラグ
	bool m_isMoveFire = true;	//動かすかどうかのフラグ

	float m_effectPlayTimer = 0.0f;		//火炎放射器を動いている間の時間計測
	float m_effectIntervalTimer = 0.0f;	//火炎放射器を止まっている間の時間計測
};
