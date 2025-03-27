//=================================================================================================
//
//	_CharaSele Player ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "_CharaSele_Player.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	_CharaSele_Player::_CharaSele_Player ()
	{
		m_chara_img = std::make_shared < CharaSele_Image > ();
	}

	_CharaSele_Player::~_CharaSele_Player ()
	{
	}

	void _CharaSele_Player::LoadTx ( P_ChSl_Img_Cmn pCmn )
	{
		m_chara_img->LoadTx ( pCmn );
	}

	void _CharaSele_Player::PlayerInit ( PLAYER_ID id )
	{
		m_chara_img->PlayerInit ( id );
	}

	void _CharaSele_Player::ParamInit ( P_Param prm )
	{
	}

	void _CharaSele_Player::Move ()
	{
		TASK_VEC::Move ();
	}


}	//namespace GAME

