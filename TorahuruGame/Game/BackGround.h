#pragma once
class BackGround :public IGameObject
{

public:
    BackGround();
    ~BackGround();
    bool Start();
    void Update();

    //�`��֐�
    void Render(RenderContext& rc);
    void SetPosition(const Vector3& position)

    {
        m_position = position;//�|�W�V����
    }
    void SetRotation(const Quaternion& rotation) {
        m_rotation = rotation;

    }



public://���Ƃ��͂���������ɍ��K�v������B
    //���f�������_�[
    ModelRender modelRender;
    Vector3 m_position;
    Vector3 m_scale = Vector3::One;
    Quaternion m_rotation;
    PhysicsStaticObject  m_physicsStaticObject;
};



