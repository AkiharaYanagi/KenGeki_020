//=================================================================================================
//
//	G_Ftg ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	UP_G_Ftg	G_Ftg::m_inst;

	G_Ftg::G_Ftg ()
	{
		Init ();
	}

	G_Ftg::~G_Ftg ()
	{
	}

	void G_Ftg::Init ()
	{
		//基準の位置
		float averagex = (PLAYER_1_BASE_X + PLAYER_2_BASE_X) * 0.5f;	//中心
		float window_half = GAME_WINDOW_WIDTH * 0.5f;	//表示ウィンドウの中心(半分)
		float posMutualBase_x = window_half - averagex;
		m_posMutualBase = VEC2 ( posMutualBase_x, 0 );

		m_wall_L = 0;
		m_wall_R = GAME_WIDTH;
		m_chara_center_x = (float)GAME_WIDTH / 2;
		m_bResetPos = F;
		m_bWallMove = F;
		m_vel_resetPos = 40.f;
	}


	//キャラ位置による画面表示の基準位置
	//毎フレーム動作
	void G_Ftg:: CulcPosMutualBase ( VEC2 pos1p, VEC2 pos2p )
	{
		//特殊演出
		//--------------------------------------------------------------------
		//キャラ位置
		float averagex = (pos1p.x + pos2p.x) * 0.5f;	//中心
		float window_half = GAME_WINDOW_WIDTH * 0.5f;	//表示ウィンドウの中心(半分)

		//キャラの中心
		m_chara_center_x = averagex;

		//基準の位置
		float posMutualBase_x = window_half - averagex;
		//--------------------------------------------------------------------

		//画面端表示処理
		float lx = 0 - m_wall_L;		//左寄
		float rx = GAME_WINDOW_WIDTH - m_wall_R;		//右寄
		float cx = window_half - averagex;		//中央

		//==========================
		//中心位置を滑らかに修正する
		//==========================
		if ( m_bWallMove )
		{
			//新規 壁位置
			m_wall_L = m_chara_center_x - (float)GAME_WIDTH_HALF;
			m_wall_R = m_chara_center_x + (float)GAME_WIDTH_HALF;

			//目標値に向かって減衰
			lx = 0 - m_wall_L;		//左寄
			rx = GAME_WINDOW_WIDTH - m_wall_R;		//右寄
			cx = window_half - averagex;		//中央

			if ( m_posMutualBase.x < rx )
			{
				posMutualBase_x += m_vel_resetPos;
			}

			if ( cx < m_posMutualBase.x )
			{
				m_posMutualBase.x -= m_vel_resetPos;
			}
		}
		else
		{
			//通常時
			
			//左寄
			//画面左端から表示半分左側のとき
			if ( averagex < m_wall_L + window_half )
			{
				posMutualBase_x = lx;
			}
			//右寄
			//画面右端から表示半分右側のとき
			else if ( averagex > m_wall_R - window_half )
			{
				posMutualBase_x = rx;
			}
			//中央
			else
			{
				posMutualBase_x = cx;
			}

			//計算した画面表示補正位置を保存
			m_posMutualBase = VEC2 ( posMutualBase_x, 0 );
		}

		DBGOUT_WND_F ( 0, U"m_posMutualBase.x = {}"_fmt( m_posMutualBase.x ) );
		DBGOUT_WND_F ( 1, U"m_bWallMove.x = {}"_fmt( m_bWallMove ? 1 : 0 ) );
		DBGOUT_WND_F ( 2, U"lx = {}, cx = {}, rx = {}"_fmt( lx, cx, rx ) );
#if 0
#endif // 0

		
		//------------------------------------------------------


#if 0
		//計算した画面表示補正位置を保存
		m_posMutualBase = VEC2 ( posMutualBase_x, 0 );
#endif // 0

		//通常時
		RevisedCamera ( pos1p, pos2p );
	}


	void G_Ftg::ResetWall ()
	{
#if 0

		//新規 壁位置
		m_wall_L = m_chara_center_x - (float)GAME_WIDTH_HALF;
		m_wall_R = m_chara_center_x + (float)GAME_WIDTH_HALF;

#endif // 0

		//滑らかに移動する
		m_bWallMove = T;

#if 0


		//壁の中心
		float wall_center = ( m_wall_L + m_wall_R ) * 0.5f;

		//壁リセット
		if ( m_bResetPos )
		{
			//新規 壁位置
			m_wall_L = m_chara_center_x - GAME_WIDTH_HALF;
			m_wall_R = m_chara_center_x + GAME_WIDTH_HALF;

			//1回のみ
//			m_bResetPos = F;
//			m_bWallMove = T;
		}
#endif // 0
	}



	void G_Ftg::AddAccel ( int n )
	{
		m_accel += n;
		if ( m_accel < -100 ) { m_accel = -100; }
		if ( 100 < m_accel ) { m_accel = 100; }
	}


	//カメラの画面端における補正位置
	void G_Ftg::RevisedCamera ( VEC2 pos1p, VEC2 pos2p )
	{
		//--------------------------------------------------------------------
		//キャラ位置
		float averagex = (pos1p.x + pos2p.x) * 0.5f;	//中心
		float window_half = GAME_WINDOW_WIDTH * 0.5f;	//表示ウィンドウの中心(半分)

		//キャラの中心
		m_chara_center_x = averagex;

		//基準の位置
		float posMutualBase_x = window_half - averagex;


		//画面端表示処理
		float lx = 0 - m_wall_L;		//左寄
		float rx = GAME_WINDOW_WIDTH - m_wall_R;		//右寄
		float cx = window_half - averagex;		//中央

		//--------------------------------------------------------------------

		//通常時

		//左寄
		//画面左端から表示半分左側のとき
		if ( averagex < m_wall_L + window_half )
		{
			posMutualBase_x = lx;
		}
		//右寄
		//画面右端から表示半分右側のとき
		else if ( averagex > m_wall_R - window_half )
		{
			posMutualBase_x = rx;
		}
		//中央
		else
		{
			posMutualBase_x = cx;
		}

#if 0
#endif // 0

		//計算した画面表示補正位置を保存
		m_posMutualBase = VEC2 ( posMutualBase_x, 0 );
	}



}	//namespace GAME

