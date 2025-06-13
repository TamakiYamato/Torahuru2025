#pragma once
class Game;
class BackGround;
class FirstFloor;
class SecondFloor;
class Player;
class BackGroundTwo :public IGameObject
{

public:
    BackGroundTwo();
    ~BackGroundTwo();
    bool Start();
    void Update();

    //描画関数
    void Render(RenderContext& rc);
    void SetPosition(const Vector3& position)

    {
        m_position = position;
    }
    void SetRotation(const Quaternion& rotation) {
        m_rotation = rotation;

    }
    void SetScale(const Vector3& scale) {
        m_scale = scale;
    }



public:
    ModelRender             modelRender;
    Quaternion              m_rotation;
    PhysicsStaticObject     m_physicsStaticObject;

    Vector3                 m_position;
    Vector3 m_scale = Vector3::One;
};





