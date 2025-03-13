#pragma once
class BackGround :public IGameObject
{

public:
    BackGround();
    ~BackGround();
    bool Start();
    void Update();

    //描画関数
    void Render(RenderContext& rc);
    void SetPosition(const Vector3& position)

    {
        m_position = position;//ポジション
    }
    void SetRotation(const Quaternion& rotation) {
        m_rotation = rotation;

    }



public://作るときはこっちが先に作る必要がある。
    //モデルレンダー
    ModelRender modelRender;
    Vector3 m_position;
    Vector3 m_scale = Vector3::One;
    Quaternion m_rotation;
    PhysicsStaticObject  m_physicsStaticObject;
};



