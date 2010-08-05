/*----------------------------------------------------------------
        本文件包含对于特定运营商在文件系统重建时需要自动生成的
        Service参数。
        
        请根据运营商的PRI改写本文件中的列表。
        
        最简单的修改方法：
        1.通过QPST的工具设置好需要的NV值，保存为QCN文件。
        2.使用QCN View转为txt文件。
        3.将其中的值复制到本表中。
                                                  by Newwind
----------------------------------------------------------------*/

//If any change in this file, please increase the MACRO AUTO_NV_MIN_VERSION
//It must be less than AUTO_NV_MODIFY_TIME_FOR_CUSTOMER
#define AUTO_NV_MIN_VERSION                 0x3

#if (AUTO_NV_MIN_VERSION >= AUTO_NV_MODIFY_TIME_FOR_CUSTOMER)
#error AUTO_NV_MIN_VERSION msut be less than AUTO_NV_MODIFY_TIME_FOR_CUSTOMER
#endif

#define AUTO_NV_ITME_VERSION                (AUTO_NV_CUST_CODE_ALCN + AUTO_NV_MIN_VERSION + AUTO_NV_RF_VERSION)

//NOTICE: we only auto set NAM-0's value 
//you can change those nv value for different operator.
const nv_auto_set_type nv_auto_set_svc_list[] = 
{
    {NV_SLOT_CYCLE_INDEX_I,             {0x02}},
    {NV_PREF_MODE_I,                    {0x00, 0x04}},
    {NV_PCDMACH_I,                      {0x00, 0x1b, 0x01, 0x80, 0x01}},
    {NV_SCDMACH_I,                      {0x00, 0xb3, 0x02, 0x09, 0x03}},
    //IMSI_S is store as MIN1 and MIN2
    {NV_MIN1_I,                         {0x00, 0xe7, 0xeb, 0xf9, 0x00, 0xe7, 0xeb, 0xf9, 0x00}},
    {NV_MIN2_I,                         {0x00, 0xe7, 0x03, 0xe7, 0x03}},
    {NV_MOB_TERM_HOME_I,                {0x00, 0x01, 0x01}},
    {NV_MOB_TERM_FOR_SID_I,             {0x00, 0x01, 0x01}},
    {NV_MOB_TERM_FOR_NID_I,             {0x00, 0x01, 0x01}},
    //Must be modified when IMSI_S changing.
    {NV_ACCOLC_I,                       {0x00, 0x00}},
    {NV_CURR_NAM_I,                     {0x00}},
    {NV_AUTO_NAM_I,                     {0x00}},            
    //change for certain opeartor
    {NV_NAME_NAM_I,                     {0x00, 'A', 'n', 'y', 'l', 'o', 'o', 'k', 0x00}},     
    //change for certain opeartor                     
    {NV_BANNER_I,                       {'A', 'n', 'y', 'l', 'o', 'o', 'k', 0x00}},   
    {NV_LOCK_CODE_I,                    {0x30, 0x30, 0x30, 0x30}}, 
    {NV_SEC_CODE_I,                     {0x30, 0x30, 0x30, 0x30, 0x30, 0x30}},
    {NV_IMSI_MCC_I,                     {0x00, 0x67, 0x01}},
    {NV_IMSI_11_12_I,                   {0x00, 0x5c}},
    {NV_DIR_NUMBER_I,                   {0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30}},
    {NV_PRL_ENABLED_I,                  {0x00, 0x01}},
    {NV_HOME_SID_NID_I,                 {
                                            0x00, 0x14, 0x36, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                        }},
    {NV_SID_NID_LOCK_I,                 {
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                        }},                                 
    {NV_PREF_VOICE_SO_I,                {0x00, 0x01, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00}},
    {NV_BAND_PREF_I,                    {0x00, 0xff, 0xff}},
    {NV_ROAM_PREF_I,                    {0x00, 0xff, 0x00}},    
#ifdef FEATURE_NET_LOCK
	#if defined(FEATURE_VERSION_IVIO)
    {NV_NET_LOCK_I,                     {   0x01, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0xFE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        }},
	#elif defined(FEATURE_VERSION_SMART)
	{NV_NET_LOCK_I,                     {   0x01, 0x00,
                                            0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0xFE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x70, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        }},
	#elif defined(FEATURE_VERSION_M8)
	{NV_NET_LOCK_I,                     {   0x01, 0x00,
                                            0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0xFE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x22, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        }},
	#else
	{NV_NET_LOCK_I,                     {   0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                        }},
	#endif
#endif
    {NV_RTRE_CONFIG_I,                  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
};

const byte pr_list_data[] =
{
    /* 000000 */ 0x00, 0x92, 0x00, 0x06, 0x81, 0x02, 0x40, 0x12, 0x33, 0x91, 0xB1, 0x92, 0x3C, 0x85, 0x00, 0x4E,
    /* 000010 */ 0x0E, 0xE0, 0x94, 0xBC, 0xC6, 0x07, 0x43, 0x78, 0xC1, 0x31, 0xAE, 0x26, 0x16, 0x75, 0x08, 0xC9,
    /* 000020 */ 0xCE, 0x08, 0xA5, 0x29, 0x0E, 0xF2, 0x30, 0x66, 0x8E, 0x18, 0x01, 0x05, 0x41, 0x4C, 0x3E, 0x0B,
    /* 000030 */ 0x91, 0xC4, 0x42, 0xC9, 0xA1, 0x71, 0x3D, 0x86, 0x33, 0x00, 0x6A, 0x8E, 0xA2, 0x9E, 0x00, 0x00,
    /* 000040 */ 0x80, 0x00, 0x10, 0x00, 0x05, 0x00, 0x80, 0x00, 0x00, 0x30, 0x20, 0x00, 0x45, 0xE1, 0x00, 0x40,
    /* 000050 */ 0x02, 0x2F, 0x8E, 0x02, 0x00, 0x11, 0x5C, 0x60, 0x18, 0x00, 0x8A, 0xC3, 0x00, 0xC0, 0x04, 0x56,
    /* 000060 */ 0x98, 0x06, 0x00, 0x22, 0xC8, 0xC0, 0x30, 0x01, 0x16, 0x66, 0x01, 0x80, 0x29, 0x91, 0x20, 0x10,
    /* 000070 */ 0x00, 0x00, 0x6D, 0x80, 0x80, 0x08, 0x20, 0x08, 0x05, 0x00, 0x3C, 0xF2, 0x20, 0x44, 0x30, 0xE4,
    /* 000080 */ 0x02, 0x00, 0x40, 0x24, 0x20, 0x14, 0x01, 0xC9, 0xF9, 0x00, 0x00, 0x10, 0x0B, 0x08, 0x07, 0x00,
    /* 000090 */ 0xD0, 0x43
};
   
