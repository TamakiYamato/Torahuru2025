#pragma once

class Game;
class Player;
class FloorManager;
class ReverseFloor;       
class SlowFloor;         
class BlindFloor;         

class TutorialUI:public IGameObject
{
public:
	TutorialUI();
	~TutorialUI();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// テキストの表示
	/// </summary>
	void Show();
	/// <summary>
	/// 次のUIを表示にするかのフラグ
	/// </summary>
	void Cheak();
	/// <summary>
	/// UIパネル
	/// </summary>
	void PanelUI();

	enum uiText {	//説明
		reverse,		//あべこべ床
		slow,			//鈍足床
		blind,			//視界制限床
		Stairs,			//階段
		CollectItems,	//奉納ギミック
		SolvePuzzle,	//絵合わせ
	};

	SpriteRender		m_spriteRender;
	FontRender			m_fontRender;
	Player*				m_player = nullptr;           
	Game*				m_game = nullptr;
	FloorManager*		m_floorManager = nullptr;
	ReverseFloor*		m_reverseFloor = nullptr;
	SlowFloor*			m_slowFloor = nullptr;
	BlindFloor*			m_blindFloor = nullptr;
	uiText				m_textState = reverse;
	
	wchar_t textUI[256];
	bool onGimmicPassed = true;		//次のUIを表示してよいかのフラグ。


public:

};

