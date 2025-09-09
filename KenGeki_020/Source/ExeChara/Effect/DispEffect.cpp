//=================================================================================================
//
// DispEffect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispEffect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DispEffect::DispEffect ( PAP_Tx papEfTx , float z ) 
		: mpap_EfTx ( papEfTx )
	{
//		//メイングラフィック
//		m_grp = std::make_shared < GameGraphic > ();
		m_grp = std::make_shared < GrpEf > ();
		m_grp->SetZ ( z );	//初期位置

		//テクスチャ中心位置で表示
		m_grp->SetbCenterOfTx ( F );

		AddpTask ( m_grp );
		GRPLST_INSERT ( m_grp );

		//最初から表示
		m_grp->On ();
		m_grp->SetShader ( T );


		//枠表示
		m_dispRect = std::make_shared < DispRect > ();
		AddpTask ( m_dispRect );
	}

	DispEffect::~DispEffect ()
	{
		//終了時にグラフィックタスクを外す
		GRPLST_REMOVE ( m_grp );

	}

	void DispEffect::SetpChara(P_Chara pChara)
	{
		//キャラのエフェクトテクスチャアレイを設置
		mpap_EfTx = pChara->GetpapEfTexture ();

		m_grp->ClearTexture ();
		for ( P_Tx ptx : * mpap_EfTx )
		{
			m_grp->AddpTexture ( ptx );
		}
	}


	void DispEffect::Update ( P_Script pScript, VEC2 ptEf, bool dirRight )
	{
		//Disp：スクリプトのイメージ表示位置

		//位置 (エフェクトのゲーム位置＋スクリプトの表示位置(*向き)＋キャラによる画面補正位置)
		float fDir = dirRight ? (1.f) : (-1.f);
		VEC2 tempImgPos = pScript->GetPos ();
		VEC2 imgPos = VEC2( fDir * tempImgPos.x, tempImgPos.y );
//		VEC2 imgPos = VEC2( tempImgPos.x, tempImgPos.y );
		VEC2 vecEfImg = ptEf + imgPos + G_BASE_POS ();

#if 0
		//2pのみ
		DBGOUT_WND_F ( DBGOUT_9,
			U"({},{}) = ({},{})+({},{})+({}, {})"_fmt(
				vecEfImg.x,
				vecEfImg.y,
				ptEf.x,
				ptEf.y,
				imgPos.x,
				imgPos.y,
				G_BASE_POS().x,
				G_BASE_POS().y )
			);
#endif // 0

#if 0
		//回転
		float rad = D3DX_PI * 0.01f * pScript->m_prmStaging.Rotate;
		m_grp->SetRadian ( rad * fDir );
#endif // 0

#if 0
		//スクリプトからの指定がなければテクスチャの中心
		VEC2 center { 0, 0 };
		if ( center != pScript->m_prmStaging.Rotate_center )
		{
			center = pScript->m_prmStaging.Rotate_center;
		}
		else
		{
//			center = pEfTx->GetCenter ();
			s3d::TextureDesc txDesc = pEfTx->getDesc ();
			txDesc
		}

		m_grp->SetRotationCenter ( center );
		m_grp->SetScalingCenter ( center );
#endif // 0

		//テクスチャの指定
		UINT index = pScript->GetImageIndex ();

		//表示に反映

//		m_grp->SetPos ( vecEfImg );
		m_grp->SetBase ( vecEfImg );	//Grp "Ef" Shdは基本位置指定をBaseで行う

		//拡大(向き)
//		m_grp->SetScaling ( m_w * fDir, 1.f );
		m_grp->SetScaling ( 1.f * fDir, 1.f );

#if 0

		VEC2 scaling = pScript->m_prmStaging.Scaling;
		m_grp->SetScaling ( scaling );
		VEC2 revised = m_grp->GetRevised ();
		m_grp->SetRevised ( revised + scaling * 0.5f );
#endif // 0

		//テクスチャID
		m_grp->SetIndexTexture ( index );

		//枠
		m_dispRect->Update ();
	}

	void DispEffect::SetpCharaRect ( P_CharaRect pCharaRect )
	{
		m_dispRect->SetCharaRect ( pCharaRect );
	}


}	//namespace GAME

