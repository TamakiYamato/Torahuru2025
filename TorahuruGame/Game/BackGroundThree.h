#pragma once
class BackGround;
class BackGroundTwo;
class Player;
class Enemy;
class FirstFloor;
class SecondFloor;
class ThirdFloor;
class Enemy;
class BackGroundThree:public IGameObject
{
public:
    BackGroundThree();
    ~BackGroundThree();
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



public://菴懊ｋ縺ｨ縺阪・縺薙▲縺｡縺悟・縺ｫ菴懊ｋ蠢・ｦ√′縺ゅｋ縲・
    //繝｢繝・Ν繝ｬ繝ｳ繝
    ModelRender             modelRender;
    Quaternion              m_rotation;
    PhysicsStaticObject     m_physicsStaticObject;

    Vector3                 m_position;
    Vector3 m_scale = Vector3::One;
};

