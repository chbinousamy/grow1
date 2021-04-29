//--------------------------------------------------------------------------
// Copyright (C) 2018-2021 Cisco and/or its affiliates. All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------
// http2_enum.h author Tom Peters <thopeter@cisco.com>

#ifndef HTTP2_ENUM_H
#define HTTP2_ENUM_H

#include <cstdint>

namespace Http2Enums
{
static const int MAX_OCTETS = 63780;
static const int DATA_SECTION_SIZE = 16384;
static const int FRAME_HEADER_LENGTH = 9;
static const uint32_t NO_STREAM_ID = 0xFFFFFFFF;

// Perform memory allocation and deallocation tracking for Http2Stream objects in increments of 25
static const uint32_t STREAM_MEMORY_TRACKING_INCREMENT = 25;

static const uint32_t HTTP2_GID = 121;

// Frame type codes (fourth octet of frame header)
enum FrameType : uint8_t { FT_DATA=0, FT_HEADERS=1, FT_PRIORITY=2, FT_RST_STREAM=3, FT_SETTINGS=4,
    FT_PUSH_PROMISE=5, FT_PING=6, FT_GOAWAY=7, FT_WINDOW_UPDATE=8, FT_CONTINUATION=9,
    FT__NONE=255 };

// Ordered from initial state to terminal state. Do not rearrange without careful consideration.
enum StreamState { STREAM_EXPECT_HEADERS, STREAM_EXPECT_BODY, STREAM_BODY, STREAM_COMPLETE,
    STREAM_ERROR };

// Message buffers available to clients
// This enum must remain synchronized with Http2Api::classic_buffer_names[]
enum HTTP2_BUFFER { HTTP2_BUFFER_FRAME_HEADER = 1, HTTP2_BUFFER_FRAME_DATA,
    HTTP2_BUFFER_DECODED_HEADER, HTTP2_BUFFER__MAX };

// Peg counts
// This enum must remain synchronized with Http2Module::peg_names[] in http2_tables.cc
enum PEG_COUNT { PEG_FLOW = 0, PEG_CONCURRENT_SESSIONS, PEG_MAX_CONCURRENT_SESSIONS,
    PEG_MAX_TABLE_ENTRIES, PEG_MAX_CONCURRENT_FILES, PEG_TOTAL_BYTES, PEG_MAX_CONCURRENT_STREAMS,
    PEG_FLOWS_OVER_STREAM_LIMIT, PEG_COUNT__MAX };

enum EventSid
{
    EVENT__NONE = -1,
    EVENT_INVALID_FLAG = 1,
    EVENT_INT_LEADING_ZEROS = 2,
    EVENT_INVALID_STREAM_ID = 3,
    EVENT_MISSING_CONTINUATION = 4,
    EVENT_UNEXPECTED_CONTINUATION = 5,
    EVENT_MISFORMATTED_HTTP2 = 6,
    EVENT_PREFACE_MATCH_FAILURE = 7,
    EVENT_REQUEST_WITHOUT_REQUIRED_FIELD = 8,
    EVENT_RESPONSE_WITHOUT_STATUS = 9,
    EVENT_CONNECT_WITH_SCHEME_OR_PATH = 10,
    EVENT_SETTINGS_FRAME_ERROR = 11,
    EVENT_SETTINGS_FRAME_UNKN_PARAM = 12,
    EVENT_FRAME_SEQUENCE = 13,
    EVENT_DYNAMIC_TABLE_OVERFLOW = 14,
    EVENT_INVALID_PROMISED_STREAM = 15,
    EVENT_PADDING_LEN = 16,
    EVENT_PSEUDO_HEADER_AFTER_REGULAR_HEADER = 17,
    EVENT_PSEUDO_HEADER_IN_TRAILERS = 18,
    EVENT_INVALID_PSEUDO_HEADER = 19,
    EVENT_TRAILERS_NOT_END = 20,
    EVENT_PUSH_WHEN_PROHIBITED = 21,
    EVENT_PADDING_ON_EMPTY_FRAME = 22,
    EVENT_C2S_PUSH = 23,
    EVENT_INVALID_PUSH_FRAME = 24,
    EVENT_BAD_PUSH_SEQUENCE = 25,
    EVENT_BAD_SETTINGS_VALUE = 26,
    EVENT_TOO_MANY_STREAMS = 27,
    EVENT_INVALID_RST_STREAM_FRAME = 28,
    EVENT_BAD_RST_STREAM_SEQUENCE = 29,
    EVENT_HEADER_UPPERCASE = 30,
    EVENT_INVALID_WINDOW_UPDATE_FRAME = 31,
    EVENT_WINDOW_UPDATE_FRAME_ZERO_INCREMENT = 32,
    EVENT__MAX_VALUE
};

// All the infractions we might find while parsing and analyzing a message
enum Infraction
{
    INF__NONE = -1,
    INF_INT_EMPTY_BUFF = 0,
    INF_INT_MISSING_BYTES = 1,
    INF_INT_OVERFLOW = 2,
    INF_INT_LEADING_ZEROS = 3,
    INF_STRING_EMPTY_BUFF = 4,
    INF_STRING_MISSING_BYTES = 5,
    INF_DECODED_HEADER_BUFF_OUT_OF_SPACE = 6,
    INF_HUFFMAN_BAD_PADDING = 7,
    INF_HUFFMAN_DECODED_EOS = 8,
    INF_HUFFMAN_INCOMPLETE_CODE_PADDING = 9,
    INF_MISSING_CONTINUATION = 10,
    INF_UNEXPECTED_CONTINUATION = 11,
    INF_C2S_PUSH = 12,
    INF_INVALID_PSEUDO_HEADER = 13,
    INF_PSEUDO_HEADER_AFTER_REGULAR_HEADER = 14,
    INF_REQUEST_WITHOUT_REQUIRED_FIELD = 15,
    INF_RESPONSE_WITHOUT_STATUS = 16,
    INF_HPACK_INDEX_OUT_OF_BOUNDS = 17,
    INF_INVALID_SETTINGS_FRAME = 18,
    INF_SETTINGS_FRAME_UNKN_PARAM = 19,
    INF_FRAME_SEQUENCE = 20,
    INF_INVALID_TABLE_SIZE_UPDATE = 21,
    INF_DYNAMIC_TABLE_OVERFLOW = 22,
    INF_TABLE_SIZE_UPDATE_WITHIN_HEADER = 23,
    INF_TOO_MANY_TABLE_SIZE_UPDATES = 24,
    INF_INVALID_STARTLINE = 25,
    INF_INVALID_HEADER = 26,
    INF_PADDING_LEN = 27,
    INF_PUSH_FRAME_TOO_SHORT = 28,
    INF_PSEUDO_HEADER_IN_TRAILERS = 29,
    INF_TRAILERS_NOT_END = 30,
    INF_CONNECT_WITH_SCHEME_OR_PATH = 31,
    INF_PADDING_ON_EMPTY_FRAME = 32,
    INF_BAD_PUSH_SEQUENCE = 33,
    INF_BAD_SETTINGS_PUSH_VALUE = 34,
    INF_PUSH_WHEN_PROHIBITED = 35,
    INF_INVALID_PROMISED_STREAM = 36,
    INF_INVALID_STREAM_ID = 37,
    INF_INVALID_FLAG = 38,
    INF_TRUNCATED_HEADER_LINE = 39,
    INF_REQUEST_WITHOUT_METHOD = 40,
    INF_CONNECT_WITHOUT_AUTHORITY = 41,
    INF_TOO_MANY_STREAMS = 42,
    INF_INVALID_RST_STREAM_FRAME = 43,
    INF_BAD_RST_STREAM_SEQUENCE = 44,
    INF_HEADER_UPPERCASE = 45,
    INF_INVALID_WINDOW_UPDATE_FRAME = 46,
    INF_WINDOW_UPDATE_FRAME_ZERO_INCREMENT = 47,
    INF__MAX_VALUE
};

enum HeaderFrameFlags
{
    FLAG_ACK = 0x1,
    FLAG_END_STREAM = 0x1,
    FLAG_END_HEADERS = 0x4,
    FLAG_PADDED = 0x8,
    FLAG_PRIORITY = 0x20,
    FLAG_NO_HEADER = 0x80, //No valid flags use this bit
};

enum SettingsFrameIds
{
    SFID_HEADER_TABLE_SIZE = 1,
    SFID_ENABLE_PUSH,
    SFID_MAX_CONCURRENT_STREAMS,
    SFID_INITIAL_WINDOW_SIZE,
    SFID_MAX_FRAME_SIZE,
    SFID_MAX_HEADER_LIST_SIZE,
};

enum ScanState { SCAN_FRAME_HEADER, SCAN_PADDING_LENGTH, SCAN_DATA, SCAN_EMPTY_DATA };
} // end namespace Http2Enums

#endif

