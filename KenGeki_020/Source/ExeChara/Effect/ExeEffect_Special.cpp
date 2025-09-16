//=================================================================================================
//
// ExeEffect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeEffect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//特定エフェクト処理
	void ExeEffect::PreMove_Special()
	{
		//======================================================================
		//フェラリア
		if (m_pEffect->IsName(U"4M_Shot"))
		{
			float dir = m_dirRight ? 1.f : -1.f;		//向き

			const float	g { 0.60f };
			float h_str { 0.10f };	//homing Strength
			float speed { 10.f };

			//放物線運動
			m_vel.y += g;

			const int32 TIME_0 = 0;		//射出
			const int32 TIME_1 = 8;		//初回角度
			const int32 TIME_2 = 14;	//補正
			const int32 TIME_3 = 20;	//ホーミング強


			//ターゲット方向を計算
			VEC2 toTarget = ( m_target - m_ptEffect ).Normalized ();

			if (TIME_0 <= m_count && m_count < TIME_1)
			{
				m_vel.x += dir * 0.5f;	//初速のみ向き補正
			}
			else if (TIME_1 <= m_count && m_count < TIME_2)
			{
				h_str = 0.7f;
				m_vel = m_vel * ( 1.0f - h_str ) + toTarget * h_str;
				speed = 20;
				m_vel = m_vel.Normalized() * speed;
			}
			else if (TIME_2 <= m_count && m_count < TIME_3)
			{
				h_str = 0.5f;
				m_vel = m_vel * ( 1.0f - h_str ) + toTarget * h_str;
				speed = 26;
				m_vel = m_vel.Normalized() * speed;
			}
			else if (TIME_3 <= m_count)
			{
				h_str = 0.9f;
				m_vel = m_vel * ( 1.0f - h_str ) + toTarget * h_str;
				speed = 26 + ( m_count * 0.7f );
				if ( 35 < speed ) { speed = 35; }
				m_vel = m_vel.Normalized() * speed;
			}
#if 0

			//ホーミング開始
			if (20 < m_count)
			{
				//ターゲット方向を計算
				VEC2 toTarget = ( m_target - m_ptEffect ).Normalized ();

				//ホーミング補正
				m_vel = m_vel * ( 1.f - h_str ) + toTarget * h_str;
				m_vel = m_vel.Normalized () * speed;


				float rad = atan2f ( m_vel.y, m_vel.x );
				P_Grp pGrp = m_dispEffect->GetpGrp ();
				pGrp->SetRadian ( rad );
			}

#endif // 0


			//位置更新
			m_ptEffect += m_vel;

			//角度
			float rad = atan2f ( m_vel.y, m_vel.x );

			//方向調整
			if ( ! m_dirRight ) { rad += D3DX_PI; }

			P_Grp pGrp = m_dispEffect->GetpGrp ();
			pGrp->SetRadian ( rad );


			//終了
			++ m_count;

	//		if ( (float)GROUND_Y < m_ptEffect.y ) { m_end = T; }
			if (180 < m_count) { m_end = T; }
		}
		
		if (m_pEffect->IsName(U"4H_Shot"))
		{
			if ( m_hit )
			{
				//攻撃枠を空にする
				m_charaRect->ResetARect ();
			}
		}

		//======================================================================
		//月日星
		if ( m_pEffect->IsName( U"OD0" ) )
		{
			if (m_pScript->GetFrame() == 0)
			{
				//拡大
//				m_pScript->m_prmStaging.Scaling = VEC2 ( 2.f, 2.f );
			}
		}

		//======================================================================
		//Enemy_0
		if ( m_pEffect->IsName ( U"Laser_m" ) )
		{
			static float w = 1.f;
			m_dispEffect->SetW ( w += 1.f );
			m_pScript->m_prmStaging.Rotate_center = VEC2 ( 0, 128 );
			if ( m_pEffect->IsEndScript ( m_frame ) )
			{
				m_dispEffect->SetW ( w = 0 );
			}
		}
		//======================================================================
	}


	void ExeEffect::PostMove_Special()
	{
		//----------------------------------
		//	Ef個別指定
		//----------------------------------
		if ( m_pEffect->GetName () == U"空中竜巻_鞘" )
		{
			if ( m_ptEffect.y >= (float)GROUND_Y )
			{
				m_ptEffect.y = GROUND_Y;
				m_vel.x = 0;
				m_vel.y = 0;
				m_acc.x = 0;
				m_acc.y = 0;
			}
		}


	}


}	//namespace GAME

