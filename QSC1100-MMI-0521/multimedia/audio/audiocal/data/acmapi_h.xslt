<?xml version="1.0" encoding="utf-16"?>

<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text" encoding="us-ascii"/>
  <xsl:template match="/CALIBRATION_DATABASE">
<![CDATA[
#ifndef ACMAPI_H
#define ACMAPI_H
/** 
\file ***************************************************************************
*
*                                   A C M A P I    H E A D E R    F I L E
*
*DESCRIPTION: This header file contains all the definitions that are required to
* to interface with audio calibration data tables in voccal.c/sndcal.c.
*
* Going forward, Source Generator tool is going to create this file from 
* audio calibration file (XML file) during build process.
*
*Copyright (c) 2008 by QUALCOMM, Incorporated.  All Rights Reserved.
*******************************************************************************
*/
/* <EJECT> */
/**
\file ***************************************************************************
*
*                      EDIT HISTORY FOR FILE
*
*  This section contains comments describing changes made to this file.
*  Notice that changes are listed in reverse chronological order.
*   
*  $Header: //depot/asic/msmshared/services/avs/acmapi.h#1 $ $DateTime: 2007/01/19 21:12:52 $ $Author: adiseshu $
*
*when         who     what, where, why<br>
*--------   ---     ----------------------------------------------------------<br>
*01/25/08   mas    created  file<br>
*
*******************************************************************************
*/

/*
      --------------------
      |include files                |
      --------------------
 */

#include "comdef.h"
#include "qdspcmd.h"
#include "acm.h"

/**
* FUNCTION acmapi_get_feature_info
*
* DESCRIPTION : returns a byte array indicating TRUE if feature is enabled and FALSE if 
* feature is disabled. 
*
* This function should be generated automatically from audio cal xml file in future
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_NONE if success
* ACM_ERR_CALFILE_MISMATCH if build guid doesn't matches
*
* SIDE EFFECTS: None
*/
extern acm_error_code acmapi_get_feature_info
(
   byte *req_buf_ptr,
   uint32* req_buf_length,
   byte **resp_buf_ptr,
   uint32 *resp_buf_length
);

/**
* FUNCTION acmapi_get_calunit_from_guid
*
* DESCRIPTION : finds matching Calunit from map for paased guid
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_calunit_enum
* if matching guid found in map enum elelment if found 
* else CALUNIT_UNKNOWN
*
* SIDE EFFECTS: None
*/
extern acm_calunit_enum acmapi_get_calunit_from_guid
(
   acm_guid *guid
);
]]>
    <xsl:apply-templates  select="CALUNITS"/>
<![CDATA[
/**
* FUNCTION acmapi_get_volume_levels_calunit_size
*
* DESCRIPTION : calculates volume levels calunit size. 
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: None
*/
extern acm_error_code acmapi_get_volume_levels_calunit_size
(
  audio_filter_indices_struct *audio_filter_indices_ptr,
  uint32 *volume_level_size
);

/**
* FUNCTION : acmapi_get_volume_levels_data
*
* DESCRIPTION : copies volume levels  data from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read into buffer
*/
extern acm_error_code acmapi_get_volume_levels_data
(
  snd_cal_control_type *audio_config_ptr,
  byte **snd_cal_calunit_resp_buf_ptr
);
/**
* FUNCTION : acmapi_set_volume_levels_data
*
* DESCRIPTION : copies volume levels data from filter structure to buffer
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read from buffer
* decrements the remaining buffer length by number of bytes read from buffer
*/
extern acm_error_code acmapi_set_volume_levels_data
(
  snd_cal_control_type *audio_config_ptr,
  byte **buf_ptr,
  uint32 *remaining_buf_length_ptr
);

/**
* FUNCTION : acmapi_get_gains_calunit_size
*
* DESCRIPTION : calculates gains calunit size
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: None
*/
extern uint32  acmapi_get_gains_calunit_size(void);

/**
* FUNCTION : acmapi_get_codec_st_gain
*
* DESCRIPTION : copies CODEC ST gain from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read into buffer
*/
extern acm_error_code  acmapi_get_codec_st_gain
(
  uint16 *codec_st_gain_ptr,
  byte **buf_ptr
);

/**
* FUNCTION : acmapi_set_codec_st_gain
*
* DESCRIPTION : copies CODEC STgain from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read
* decrements remaining buffer length by numbr of bytes read
*/
extern acm_error_code  acmapi_set_codec_st_gain
(
uint16 *codec_st_gain_ptr,
byte **buf_ptr,
uint32 *remaining_buf_length_ptr
);

/**
* FUNCTION : acmapi_get_codec_rx_gain
*
* DESCRIPTION : copies CODEC RX gain from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read into buffer
*/
extern acm_error_code  acmapi_get_codec_rx_gain
(
  uint16 *codec_rx_gain_ptr,
  byte **buf_ptr
);

/**
* FUNCTION : acmapi_set_codec_rx_gain
*
* DESCRIPTION : copies CODEC RX gain from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read
* decrements remaining buffer length by numbr of bytes read
*/
acm_error_code  acmapi_set_codec_rx_gain
(
uint16 *codec_rx_gain_ptr,
byte **buf_ptr,
uint32 *remaining_buf_length_ptr
);
/**
* FUNCTION : acmapi_get_codec_tx_gain
*
* DESCRIPTION : copies CODEC TX gain from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read into buffer
*/
extern acm_error_code  acmapi_get_codec_tx_gain
(
  uint16 *codec_tx_gain_ptr,
  byte **buf_ptr
);

/**
* FUNCTION : acmapi_set_codec_tx_gain
*
* DESCRIPTION : copies CODEC TX gain from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read
* decrements remaining buffer length by numbr of bytes read
*/
extern acm_error_code  acmapi_set_codec_tx_gain
(
uint16 *codec_tx_gain_ptr,
byte **buf_ptr,
uint32 *remaining_buf_length_ptr
);

/**
* FUNCTION : acmapi_get_tx_dtmf_gain
*
* DESCRIPTION : copies TX DTMF gain from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read into buffer
*/
extern acm_error_code  acmapi_get_tx_dtmf_gain
(
  uint16 *tx_dtmf_gain_ptr,
  byte **buf_ptr
);

/**
* FUNCTION : acmapi_set_tx_dtmf_gain
*
* DESCRIPTION : copies TX DTMF gain from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read
* decrements remaining buffer length by numbr of bytes read
*/
extern acm_error_code  acmapi_set_tx_dtmf_gain
(
uint16 *tx_dtmf_gain_ptr,
byte **buf_ptr,
uint32 *remaining_buf_length_ptr
);

/**
* FUNCTION : acmapi_get_tx_gain
*
* DESCRIPTION : copies TX Voice Volume from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read into buffer
*/
extern acm_error_code  acmapi_get_tx_gain
(
  uint16 *tx_gain_ptr,
  byte **buf_ptr
);

/**
* FUNCTION : acmapi_set_tx_gain
*
* DESCRIPTION : copies TX Voice Volume from buffer to structure
*
* DEPENDENCIES: None 
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read
* decrements remaining buffer length by numbr of bytes read
*/
extern acm_error_code  acmapi_set_tx_gain
(
uint16 *tx_gain_ptr,
byte **buf_ptr,
uint32 *remaining_buf_length_ptr
);

#endif /*ACMAPI_H*/
]]>    
    </xsl:template>

  <!-- Process CALUNITS Template -->
  <xsl:template match="CALUNITS">
      <!--Process calunits -->
      <xsl:call-template name="process_calunits"/>
  </xsl:template>

  <xsl:template name="process_calunits">
    <xsl:for-each select="*[not(@name='Sound Calibration')]
                           [not(@name='Gains')]">
      <xsl:call-template name="FEATURISATION"/>
      <xsl:if test="name(current()) = 'CALUNIT'">
        <xsl:for-each select="*">
          <xsl:call-template name="FEATURISATION"/>
          <xsl:if test="name(current()) = 'ELEMENT'">
            <xsl:call-template name="process_cal_element"/>
          </xsl:if>
        </xsl:for-each>
        <xsl:variable name="fn_name" select="
          translate(translate(@name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ',
          'abcdefghijklmnopqrstuvwxyz'),' ', '_')"/>

        <!-- get calunit size function -->
        <xsl:text>&#xa;/**&#xa;* FUNCTION : acmapi_get_</xsl:text>
        <xsl:copy-of select="$fn_name"/>
        <xsl:text>_size 
*
* DESCRIPTION : calculate </xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text> calunit size. 
*
* DEPENDENCIES: None
*
* RETURN VALUE: uint32 size - size of the calunit
*
* SIDE EFFECTS: None
*/
uint32 acmapi_get_</xsl:text>
        <xsl:copy-of select="$fn_name"/>
        <xsl:text>_calunit_size(void);&#xa;</xsl:text>
      </xsl:if>
      <xsl:if test="name(current()) = 'ELEMENT'">
        <xsl:call-template name="process_cal_element"/>
      </xsl:if>
    </xsl:for-each>
  </xsl:template>

  <xsl:template name="process_cal_element">
    <xsl:variable name="datatype">
      <xsl:value-of select="@datatype"/>
    </xsl:variable>
    <xsl:variable name="struct_ptr">
      <xsl:value-of select="concat(substring-after(
                                  substring-before(
                                  @datatype,'_type'),'qdsp_cmd_'),
                                  '_ptr')"/>
    </xsl:variable>

    <!-- get size function -->
    <xsl:call-template name="get_size_fn_header"/>


    <!-- get function -->
    <xsl:call-template name="get_fn_header"/>
    <xsl:text>&#xa;acm_error_code  acmapi_get_</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>&#xa;( &#xa;&#x20;&#x20;</xsl:text>
    <xsl:value-of select="@datatype"/>
    <xsl:text> *</xsl:text>
    <xsl:value-of select="$struct_ptr"/>
    <xsl:text>, &#xa;&#x20;&#x20;byte **buf_ptr&#xa;);&#xa;</xsl:text>

    <!-- set function -->
    <xsl:call-template name="set_fn_header"/>
    <xsl:text>&#xa;acm_error_code  acmapi_set_</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>&#xa;( &#xa;&#x20;&#x20;</xsl:text>
    <xsl:value-of select="@datatype"/>
    <xsl:text> *</xsl:text>
    <xsl:value-of select="$struct_ptr"/>
    <xsl:text>, &#xa;&#x20;&#x20;byte **buf_ptr,&#xa;&#x20;&#x20;uint32 *remaining_buf_length_ptr&#xa;);&#xa;</xsl:text>
  </xsl:template>
  
  <!--print get size funtion header -->
  <xsl:template name="get_size_fn_header">
    <xsl:text>&#xa;/**&#xa;* FUNCTION : acmapi_get_</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>_size
*
* DESCRIPTION : calculate </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text> size.
*
* DEPENDENCIES: None
*
* RETURN VALUE: uint32 size - size of the filter
*
* SIDE EFFECTS: None
*/
uint32 acmapi_get_</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>_size(void);&#xa;</xsl:text>
  </xsl:template>

  <!--print get function header -->
  <xsl:template name="get_fn_header">
    <xsl:text>&#xa;/**&#xa;* FUNCTION : acmapi_get_</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text> 
*
* DESCRIPTION : copies </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text> data from filter structure to buffer 
*
* DEPENDENCIES: None
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes read from buffer
* decrements the remaining buffer length by number of bytes read from buffer
*/</xsl:text>
  </xsl:template>

  <!--print set function header -->
  <xsl:template name="set_fn_header">
    <xsl:text>&#xa;/**&#xa;* FUNCTION : acmapi_set_</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text> 
*
* DESCRIPTION : copies </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text> data from buffer to filter structure 
*
* DEPENDENCIES: None
*
* RETURN VALUE: acm_error_code
* ACM_ERR_UNKNOWN
* ACM_ERR_NONE if success
* ACM_ERR_UNEXPECTED_BUF_SIZE if buffer size doesnot matches with expected structure size
*
* SIDE EFFECTS: Modifies calibration table
* increments the buffer pointer by number of bytes wrote to buffer
*/</xsl:text>
  </xsl:template>

  <xsl:template name="FEATURISATION">
    <xsl:if test="name(current()) = 'FEATURISATION'">
      <xsl:apply-templates select="FEATURE_IF"/>
      <xsl:apply-templates select="FEATURE_IF_BINARY"/>
      <xsl:apply-templates select="FEATURE_ELIF"/>
      <xsl:apply-templates select="FEATURE_ELIF_BINARY"/>
      <xsl:apply-templates select="FEATURE_ELSE"/>
      <xsl:text>#endif/* </xsl:text>
      <xsl:value-of select="child::*/attribute::name"/>
      <xsl:variable name="OPR">
        <xsl:value-of select="child::FEATURE_IF_BINARY/BINARY_OPERATION/@opr"/>
      </xsl:variable>
      <xsl:for-each select="child::FEATURE_IF_BINARY/BINARY_OPERATION/OPERAND">
        <xsl:text>(</xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text>)</xsl:text>
        <xsl:if test="position() != last()">
          <xsl:if test="string($OPR)=string('OR')">
            <xsl:text disable-output-escaping="yes"> || </xsl:text>
          </xsl:if>
          <xsl:if test="string($OPR)=string('AND')">
            <xsl:text disable-output-escaping="yes"> &amp;&amp; </xsl:text>
          </xsl:if>
        </xsl:if>
      </xsl:for-each>
      <xsl:text> */&#xa;</xsl:text>
    </xsl:if>
  </xsl:template>

  <!-- FEATURE_IF Template -->
  <xsl:template match="FEATURE_IF">
    <xsl:text>&#xa;#ifdef </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="process_calunits"/>
  </xsl:template>

  <!-- FEATURE_ELIF Template -->
  <xsl:template match="FEATURE_ELIF">
    <xsl:text>&#xa;#elif </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="process_calunits"/>
  </xsl:template>

  <!-- FEATURE_IF_BINARY Template -->
  <xsl:template match="FEATURE_IF_BINARY">
    <xsl:text>&#xa;#if </xsl:text>
    <xsl:call-template name="BINARY_OPERATION"/>
    <xsl:text>&#xa;&#x20;&#x20;</xsl:text>
    <xsl:call-template name="process_calunits"/>
  </xsl:template>

  <!-- FEATURE_ELIF_BINARY Template -->
  <xsl:template match="FEATURE_ELIF_BINARY">
    <xsl:text>&#xa;#elif </xsl:text>
    <xsl:call-template name="BINARY_OPERATION"/>
    <xsl:text>&#xa;&#x20;&#x20;</xsl:text>
    <xsl:call-template name="process_calunits"/>
  </xsl:template>

  <!-- BINARY_OPERATION Template -->
  <xsl:template name="BINARY_OPERATION">
    <xsl:for-each select="*">
      <xsl:if test="name(current()) = 'BINARY_OPERATION'">
        <xsl:variable name="OPR">
          <xsl:value-of select="@opr"/>
        </xsl:variable>
        <!-- Go for operands now -->
        <xsl:for-each select="OPERAND">
          <xsl:text>defined(</xsl:text>
          <xsl:value-of select="@name"/>
          <xsl:text>)</xsl:text>
          <xsl:if test="position() != last()">
            <xsl:if test="string($OPR)=string('OR')">
              <xsl:text disable-output-escaping="yes"> || </xsl:text>
            </xsl:if>
            <xsl:if test="string($OPR)=string('AND')">
              <xsl:text disable-output-escaping="yes"> &amp;&amp; </xsl:text>
            </xsl:if>
          </xsl:if>
        </xsl:for-each>
        <!-- place the operator before any embedded binary opr -->
        <xsl:if test="count(current()/child::BINARY_OPERATION) > 0">
          <xsl:if test="string(@opr)=string('OR')">
            <xsl:text disable-output-escaping="yes"> || </xsl:text>
          </xsl:if>
          <xsl:if test="string(@opr)=string('AND')">
            <xsl:text disable-output-escaping="yes"> &amp;&amp; </xsl:text>
          </xsl:if>
        </xsl:if>
        <!-- Recursive Call -->
        <xsl:call-template name="BINARY_OPERATION"/>
      </xsl:if>
    </xsl:for-each>
  </xsl:template>

  <!-- FEATURE_ELSE Template -->
  <xsl:template match="FEATURE_ELSE">
    <xsl:text>#else </xsl:text>
    <xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="process_calunits"/>
  </xsl:template>

</xsl:stylesheet> 
