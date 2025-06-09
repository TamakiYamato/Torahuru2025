#pragma once
//#include"Title.h"
//#include"FirstFloor.h"
//#include"SecondFloor.h"
//#include"TutorialUI.h"
//class FirstFloor;
//class SecondFloor;
//class TutorialUI;
//enum SceneID
//{
//    S_Title, // タイトル
//    S_Stage1,// ステージ1
//    S_Stage2,// ステージ2
//    Invalid  //無効なID
//};
//
//class IScene
//{
//public:
//    IScene() {}; // コンストラクタ
//    virtual ~IScene() {}; // 純粋仮想のデストラクタも定義。
//    virtual bool Start() = 0; // シーンの初期化
//    virtual void Update() = 0; // シーンの更新
//
//    Title* m_title = nullptr; // タイトルシーンのポインタ
//    Game* m_game = nullptr;
//    FirstFloor* m_firstfloor = nullptr; // ステージ1のポインタ
//    SecondFloor* m_secondfloor = nullptr; // ステージ2のポインタ
//
//};
//
//class Scene : public IGameObject
//{
//public:
//    Scene() {};
//    ~Scene() {};
//    bool Start();
//    void Update();
//};
//
//class FirstFloorScene : public IScene
//{
//public:
//    FirstFloorScene() {};
//    ~FirstFloorScene() {};
//
//    bool Start() override;
//    void Update() override;
//
//    bool m_isGameClearFlag = false; // ゲームクリアフラグ
//
//};
//
//class SecondFloorScene : public IScene  
//{  
//public:  
//    SecondFloorScene() {};  
//    ~SecondFloorScene() {};  
//
//    bool Start() override;  
//    void Update() override;  
//
//    bool m_isGameClearFlag = false; // ゲームクリアフラグ  
//};
//
//class TitleScene : public IScene
//{
//public:
//    TitleScene() {};
//    ~TitleScene() {};
//
//    bool Start() override;
//    void Update() override;
//
//};
//
//
//class Scene_Manager : public IScene
//{
//private:
//    IScene* scene = nullptr;
//    static Scene_Manager* instance;// シングルトンインスタンス
//    Scene_Manager() {}; // コンストラクタはprivateにする
//
//public:
//    ~Scene_Manager() {};  // デストラクタはpublicにする
//    bool Start()override;
//    void Update()override;
//    void ChangeScene();
//    // GetInstance()でシーンマネージャーを取得する。
//    // IGameObjectを持ってない →  直接呼び出す。
//    static Scene_Manager* GetInstance()
//    {
//        if (instance == nullptr)
//        {
//            instance = new Scene_Manager();
//        }
//
//        return instance;
//
//    }
//
//    void SetRequest(SceneID id)
//    {
//        requestSceneID = id;
//    };
//    SceneID requestSceneID;
//
//
//};