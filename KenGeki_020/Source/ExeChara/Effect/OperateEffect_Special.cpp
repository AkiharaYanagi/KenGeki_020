//=================================================================================================
//
// OperateEffect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "OperateEffect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//特定エフェクト処理
	void OperateEffect::Generate_Special
	(
		P_ExEf pExeEffect, P_Effect pEffect, P_EfGnrt pEfGnrt,
		VEC2 ptChara, bool dirRight
	)
	{
		(void)ptChara;

		//----------------------------------
		//	Ef個別指定
		//----------------------------------
		if ( pEffect->GetName () == U"空中竜巻_鞘" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"HitLine0" ) { /* pExeEffect->SetShader ( F ); */ }
		if ( pEffect->GetName () == U"HitLine1" ) { /* pExeEffect->SetShader ( F ); */ }
		if ( pEffect->GetName () == U"HitSmoke" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"HitSmoke1" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"DustCloud" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"Guard" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"地面" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"Ukemi" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"EX" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"暁0" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"暁1" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"颯0" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"颯1" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"贐" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"極" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"万雷発生" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"万雷中派生" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"OD_A_R" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"OD_A_L" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"OD_A_G" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"Ef_テル・プム" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"Ef_ニャムヒー" ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->GetName () == U"4L_Shot" ) { pExeEffect->SetShader ( F ); }



		if ( pEffect->GetName () == U"4H_Shot" )
		{
			pExeEffect->SetImmortal ( T );
		}


		if ( pEffect->GetName () == U"4M_Shot" )
		{
			int x = (int)pEfGnrt->GetPos().x;

			if (dirRight)
			{
				switch ( x )
				{
				case  100: pExeEffect->SetVel ( VEC2{  6.0, -10.5 } ); break;
				case   80: pExeEffect->SetVel ( VEC2{  7.0, -10.5 } ); break;
				case   60: pExeEffect->SetVel ( VEC2{  8.0, -10.5 } ); break;
				case -140: pExeEffect->SetVel ( VEC2{ -8.0, -10.5 } ); break;
				case -150: pExeEffect->SetVel ( VEC2{ -7.0, -10.5 } ); break;
				case -160: pExeEffect->SetVel ( VEC2{ -6.0, -10.5 } ); break;
				default: break;
				}
			}
			else
			{
				switch ( x )
				{
				case  100: pExeEffect->SetVel ( VEC2{ -6.0, -10.5 } ); break;
				case   80: pExeEffect->SetVel ( VEC2{ -7.0, -10.5 } ); break;
				case   60: pExeEffect->SetVel ( VEC2{ -8.0, -10.5 } ); break;
				case -140: pExeEffect->SetVel ( VEC2{  8.0, -10.5 } ); break;
				case -150: pExeEffect->SetVel ( VEC2{  7.0, -10.5 } ); break;
				case -160: pExeEffect->SetVel ( VEC2{  6.0, -10.5 } ); break;
				default: break;
				}
			}


			pExeEffect->SetCalcOff ( T );
			pExeEffect->SetShader ( F );

		}
	}


}	//namespace GAME

