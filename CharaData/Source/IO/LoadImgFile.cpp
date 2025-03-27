//=================================================================================================
//
// LoadImgFile ソースファイル
//
//=================================================================================================
#include "LoadImgFile.h"
namespace FS = std::filesystem;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	PAP_Tx LoadImgFile::Do ( s3d::String filepath )
	{
		//Unicode ロケールの設定
		::setlocale ( LC_ALL, "japanese" );

		std::locale loc ( "en_US.UTF-8" );
		std::wcout.imbue ( loc );


		PAP_Tx paptx = std::make_shared < AP_Tx > ();

		//ファイル存在確認
		if ( ! FS::exists  ( filepath.str() ) ) { return paptx; }

		//バイナリリーダ
		s3d::BinaryReader br { filepath };
		if ( not br ) { throw s3d::Error { filepath }; }

		//ファイル数
		uint32 filenum = 0;
		br.read ( filenum );

		for ( uint32 nf = 0; nf < filenum; ++ nf )
		{
			//名前
			byte namesize = 0;
			br.read ( namesize );

			UP_BYTE buf = std::make_unique < byte [] > ( namesize );
	//		br.read ( buf.get(), 0, namesize );
	//		std::string name;
			for ( uint32 i = 0; i < namesize; ++ i )
			{
				br.read ( buf[i] );
			}
			std::string name ( (char*)buf.get(), namesize );

			s3d::String s3dStr = s3d::Unicode::FromUTF8 ( name );

			//サイズ
			uint32 imgsize = 0;
			br.read ( imgsize );

			UP_BYTE bufImg = std::make_unique < byte [] > ( imgsize );
			br.read ( bufImg.get(), imgsize );

			//メモリ上からテクスチャに変換
			s3d::MemoryReader mr ( bufImg.get(), imgsize );
			P_Tx ptx = std::make_shared < s3d::Texture > ( std::move ( mr ) );


			//配列に追加
			paptx->push_back ( ptx );
		}


		return paptx;
	}


	void LoadImgFile::Conversion ( s3d::String filepath )
	{

		//ファイル存在確認
		if ( ! FS::exists  ( filepath.str() ) ) { return; }

		//バイナリリーダ
		s3d::BinaryReader br { filepath };
		if ( not br ) { throw s3d::Error { filepath }; }

		//バイナリライタ
		s3d::String filepath_tx = filepath.substr ( 0, filepath.length () - 4 ) + U".tx";
		s3d::BinaryWriter bw { filepath_tx };


		//ファイル数
		uint32 filenum = 0;
		br.read ( filenum );

		for ( uint32 nf = 0; nf < filenum; ++ nf )
		{
			//名前
			byte namesize = 0;
			br.read ( namesize );

			UP_BYTE buf = std::make_unique < byte [] > ( namesize );
	//		br.read ( buf.get(), 0, namesize );
	//		std::string name;
			for ( uint32 i = 0; i < namesize; ++ i )
			{
				br.read ( buf[i] );
			}
			std::string name ( (char*)buf.get(), namesize );

			s3d::String s3dStr = s3d::Unicode::FromUTF8 ( name );

			//サイズ
			uint32 imgsize = 0;
			br.read ( imgsize );

			UP_BYTE bufImg = std::make_unique < byte [] > ( imgsize );
			br.read ( bufImg.get(), imgsize );

			//メモリ上からテクスチャに変換
			s3d::MemoryReader mr ( bufImg.get(), imgsize );
			P_Tx ptx = std::make_shared < s3d::Texture > ( std::move ( mr ) );


			//書込
			s3d::Texture tx;
			tx = *ptx;

			//サイズ
			size_t size_tx = sizeof ( *ptx );
			bw.write ( size_tx );
			//データ
			bw.write ( ptx.get(),  size_tx );

#if 0
			//シリアライズ
			s3d::String filepath_tx = filepath.substr ( 0, filepath.length () - 4 ) + U".tx";
			s3d::Serializer < s3d::BinaryWriter > bw { filepath_tx };
			bw ( filepath_tx );
#endif // 0
		}

#if 0

		//シリアライズ
		s3d::String filepath_tx = filepath.substr ( 0, filepath.length () - 4 ) + U".tx";
		s3d::Serializer < s3d::BinaryWriter > bw { filepath_tx };
		bw ( filepath_tx );

		s3d::Texture tx;
//		bw ( tx );

#endif // 0
	}

	PAP_Tx LoadImgFile::LoadTx ()
	{
		PAP_Tx paptx = std::make_shared < AP_Tx > ();
		return paptx;
	}


	//Img->PAP_Tx
	PAP_Tx LoadImgFile::LoadImg ()
	{
		PAP_Tx paptx = std::make_shared < AP_Tx > ();
		return paptx;
	}

	//Atlas->PAP_Tx
	PAP_Tx LoadImgFile::LoadAtlas ( s3d::String filepath )
	{
		//atlasをデシリアライズ
		Atlas atlas;
		s3d::Deserializer < s3d::BinaryReader > br { filepath };

		if ( not br )
		{
			return std::make_shared < AP_Tx > ();
		}

		br ( atlas );

		return atlas.GetpapTx ();
	}


	//LZ4 -> PAP_Tx
	PAP_Tx LoadImgFile::LoadLz4 ( s3d::String filepath )
	{
		//ファイル読込
		s3d::BinaryReader br { filepath };

		//圧縮サイズ
		size_t cmprsdSz = br.size();

		//元サイズを読取
		size_t originSz = 0;
		br.read ( originSz );

		//圧縮データを読取
		s3d::Blob cmprsBlob { cmprsdSz };
		br.read ( cmprsBlob.data(), sizeof ( originSz ), cmprsdSz );

		//解凍サイズ
		int dcmprsSz = (int)originSz;
		//std::vector < char > dcmprsBuf ( dcmprsSz );
		s3d::Blob dcmprsBuf ( originSz );

		//解凍
		LZ4_decompress_safe ( (const char *)cmprsBlob.data(), (char*)dcmprsBuf.data(), (int)cmprsdSz, dcmprsSz );

		size_t szDmprsBuf = dcmprsBuf.size ();
		s3d::MemoryReader mr { dcmprsBuf };

		Atlas atlas;
		atlas.LoadMemoryStream ( mr );

		return atlas.GetpapTx ();
	}

	
	//LZ4 -> PAP_Tx
	PAP_Tx LoadImgFile::LoadLz4_Bhv ( s3d::String filepath )
	{
		return LoadLz4 ( filepath );
	}

	PAP_Tx LoadImgFile::LoadLz4_Bhv_Name ( s3d::String filepath )
	{
		s3d::String fn = filepath.substr ( 0, filepath.length() - 4 );
		s3d::String filename_bhv = fn + U"_bhv.lz4";
		return LoadLz4 ( filename_bhv );
	}

	//LZ4 -> PAP_Tx
	PAP_Tx LoadImgFile::LoadLz4_Gns ( s3d::String filepath )
	{
		return LoadLz4 ( filepath );
	}

	PAP_Tx LoadImgFile::LoadLz4_Gns_Name ( s3d::String filepath )
	{
		s3d::String fn = filepath.substr ( 0, filepath.length() - 4 );
		s3d::String filename_gns = fn + U"_gns.lz4";
		return LoadLz4 ( filename_gns );
	}


}	//namespace GAME

