#pragma once
class Game;
class Player;
class ReverseFloor;
class SlowFloor;
class BlindFloor;
class FloorManager : public IGameObject
{
public:
	FloorManager();
	~FloorManager();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void FindFloor();				//縺吶∋縺ｦ蠎翫ｒ隕九▽縺代ｋ
	void SetPointLight();			//繝昴う繝ｳ繝医Λ繧､繝医・蛻晄悄險ｭ螳壹→譏弱ｋ縺募､画峩
	void DeletePointLight();		//繝昴う繝ｳ繝医Λ繧､繝医・delele
	void AddStatus();				//蜉ｹ譫懊・蜿肴丐
	void AddStatusTimer();			//蜉ｹ譫懈凾髢・
	void CalcStatusTime();			//蜉ｹ譫懈凾髢薙・險域ｸｬ縲∫憾諷九・螟画峩
	void RevertState();				//蜿励￠縺溷柑譫懊ｒ謌ｻ縺・

	/// <summary>
	/// 迚ｹ谿雁ｺ翫・繧ｹ繝・・繧ｿ繧ｹ
	/// </summary>
	enum FloorState {
		Normal,			//蜉ｹ譫懊↑縺励・
		ReverseState,	//縺ゅ∋縺薙∋蠎翫・
		SlowState,		//驤崎ｶｳ蠎翫・
		BlindState,		//隕也阜蛻ｶ髯仙ｺ翫・
	};


	ReverseFloor*				m_reverseFloor;						//縺ゅ∋縺薙∋蠎翫・
	SlowFloor*					m_slowFloor;						//驤崎ｶｳ蠎翫・
	BlindFloor*					m_blindFloor;						//隕也阜蛻ｶ髯仙ｺ翫・
	SpriteRender*				m_spriteRender;
	FontRender*					m_fontRender;
	PointLight*					m_pointL;							//繝昴う繝ｳ繝医Λ繧､繝医・
	Player*						m_player;							//繝励Ξ繧､繝､繝ｼ縲・
	Game*						m_game = nullptr;					//繧ｲ繝ｼ繝縲・

	Vector3					pointLightPosition;
	int						m_floorState	= Normal;			//迚ｹ谿雁ｺ翫ｒ雕上ｓ縺縺九←縺・°縺ｮ繧ｹ繝・・繧ｿ繧ｹ縲・
	int						m_saveState		= Normal;			//繝励Ξ繧､繝､繝ｼ縺ｮ迥ｶ諷九ｒ菫晏ｭ倥∝､繧抵ｼ貞屓莉･荳願ｨ育ｮ励＆繧後ｋ縺ｮ繧帝亟縺舌・
	float					m_floorTimer	= 7.0f;				//迚ｹ谿雁ｺ翫・蜉ｹ譫懈凾髢薙・

private:
	bool					m_isAddStatus = false;
};

