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
	TutorialUI() {};
	~TutorialUI() {};

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// テキストの表示
	/// </summary>
	void DisplayText();
	/// <summary>
	/// 次のUIを表示にするかのフラグ
	/// </summary>
	void CheckNextUIFlag();
	/// <summary>
	/// テキストを見やすくするために背景カラーの設定
	/// </summary>
	void InitBackTextBoxColor();

	enum enUIText {	//説明
		enReverse,		//あべこべ床
		enSlow,			//鈍足床
		enBlind,		//視界制限床
		enFireTrigger,	//火炎放射器オンオフ床
		enStairs,		//階段
		enCollectItem,	//奉納ギミック
		enSolvePuzzle,	//絵合わせ
	};

	SpriteRender		m_spriteRender;
	FontRender			m_fontRender;
	Player*				m_player = nullptr;           
	Game*				m_game = nullptr;
	FloorManager*		m_floorManager = nullptr;
	ReverseFloor*		m_reverseFloor = nullptr;
	SlowFloor*			m_slowFloor = nullptr;
	BlindFloor*			m_blindFloor = nullptr;
	enUIText			m_textState = enReverse;
	
	wchar_t m_textUI[256];
	bool m_onGimmicPassed = true;		//次のUIを表示してよいかのフラグ。


public:

};

