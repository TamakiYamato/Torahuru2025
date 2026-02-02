#pragma once
class Game;
class Player;
class GameClear;
class FirstFloor;

/// <summary>
/// StairsのGameObject
/// </summary>
class Stairs :public IGameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stairs() {};

	/// <summary>
	/// スタート
	/// </summary>
	/// <returns></returns>
	bool Start();

	/// <summary>
	/// アップデート
	/// </summary>
	void Update();

	/// <summary>
	/// モデルレンダラー
	/// </summary>
	void Render(RenderContext& renderContext);

	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}
private:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Stairs() {};
private:
	PhysicsStaticObject	   m_physicsStaticObject;// 静的オブジェクト
	ModelRender            m_modelRender;// モデルの描画
	Quaternion             m_rotation;// 回転

	Player*		m_player = nullptr;                // プレイヤークラス参照
	FirstFloor* m_firstfloor = nullptr;           // ファーストフロアの定義
	CollisionObject* m_collisionObject = nullptr;// 当たり判定

	Vector3	m_scale;     // 階段のスケール
	Vector3	m_position ;// 階段のポジション
};

