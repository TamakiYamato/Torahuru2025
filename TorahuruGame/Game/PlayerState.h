#pragma once

class Player;
class IPlayerState
{
public:
	// 邏皮ｲ倶ｻｮ諠ｳ髢｢謨ｰ:螳溯｣・・縺ｧ邨ｶ蟇ｾ菴ｿ繧上↑縺代ｌ縺ｰ縺ｪ繧峨↑縺・未謨ｰ縲・
	virtual void Enter() = 0;       // 迥ｶ諷九′蛻・ｊ譖ｿ繧上▲縺滄圀縺ｫ1蠎ｦ縺縺大他縺ｰ繧後ｋ縲や・繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ
	virtual void Update() = 0;      // 譖ｴ譁ｰ縲や・繝代ャ繝峨・蜈･蜉帷ｭ峨・
	virtual void Exit() = 0;        // 迥ｶ諷九′蛻・ｊ譖ｿ繧上ｋ髫帙↓・大ｺｦ縺縺大他縺ｰ繧後ｋ縲や・ 迥ｶ諷九・蠕悟・逅・ゆｾ・ new縺励◆髫帙・蜑企勁縲・
};

class PlayerMoveState : public IPlayerState 
{
public:
	void Enter()  override;
	void Update() override;
	void Exit()   override;

	// 繝｡繝ｳ繝仙､画焚縲・
	Player*					m_requestSutate;
};

