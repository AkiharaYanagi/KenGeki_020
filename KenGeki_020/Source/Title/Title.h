//=================================================================================================
//
//	タイトル イントロダクション対応
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Title : public Scene, public std::enable_shared_from_this < Title >
	{
		P_Grp		m_bg;
		float		m_bg_x { 0 };

		P_Grp		m_logo;
		P_Grp		m_menu;
		P_Grp		m_cursor;

		P_FadeRect	m_fade_in;
		P_FadeRect	m_fade_out;
		uint32		m_plus_wait { 0 };

		float		m_cursor_scaling_vy { 0.05f };
		float		m_cursor_scaling_y { 1.f };


//		std::unique_ptr < s3d::VideoTexture >		m_test;

//		s3d::Array < int32 > delays;
//		s3d::Array < s3d::Texture > txs;

//		P_Grp		m_charaTest;


		//シーン選択
		enum TITLE_TO
		{
			TITLE_TO_BATTLE,
			TITLE_TO_TRAINING,
		};

		TITLE_TO	m_to { TITLE_TO_BATTLE };

	public:
		Title ();
		Title ( const Title & rhs ) = delete;
		~Title ();

		void ParamInit ();

		void Move ();
		void Load ();

		P_GameScene Transit ();

	private:
		void Select ();
	};

	using P_Title = std::shared_ptr < Title >;


}	//namespace GAME

