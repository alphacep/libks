/*
 * Copyright (c) 2018 SignalWire, Inc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ks_json_check.h -- Validation functions for ks_json.
 *
 */
#ifndef KS_JSON_CHECK_H
#define KS_JSON_CHECK_H

typedef int (*ks_json_check_function)(ks_json_t *, const char **);

#define JSON_CHECK_DECL(name) KS_DECLARE(int) CHECK_##name(ks_json_t *item, const char **error_msg);
#define JSON_CHECK(name, rule) KS_DECLARE(int) CHECK_##name(ks_json_t *item, const char **error_msg) { if (!ks_json_check_object(item, rule)) { *error_msg = #name " error"; return 0; }
#define JSON_CHECK_ARRAY(name, rule) KS_DECLARE(int) CHECK_##name(ks_json_t *item, const char **error_msg) { if (!ks_json_check_array_items(item, CHECK_##rule, error_msg)) { return 0; }

#define JSON_CHECK_OBJECT(name, rule) if (!CHECK_##rule(ks_json_get_object_item(item, #name), error_msg)) { return 0; }
#define JSON_CHECK_OBJECT_OPTIONAL(name, rule) if (ks_json_get_object_item(item, #name) && !CHECK_##rule(ks_json_get_object_item(item, #name), error_msg)) { return 0; }
#define JSON_CHECK_ARRAY_ITEMS(name, rule) if (!ks_json_check_array_items(ks_json_get_object_item(item, #name), CHECK_##rule, error_msg)) { return 0; }

#define JSON_CHECK_NUMBER(name, rule) if (!ks_json_check_number_##rule(ks_json_get_object_item(item, #name))) { *error_msg = #name " error"; return 0; }
#define JSON_CHECK_NUMBER_OPTIONAL(name, rule) if (ks_json_get_object_item(item, #name) && !ks_json_check_number_##rule(ks_json_get_object_item(item, #name))) { *error_msg = #name " error"; return 0; }
#define JSON_CHECK_STRING(name, rule) if (!ks_json_check_string_##rule(ks_json_get_object_item(item, #name))) { *error_msg = #name " error"; return 0; }
#define JSON_CHECK_STRING_OPTIONAL(name, rule) if (ks_json_get_object_item(item, #name) && !ks_json_check_string_##rule(ks_json_get_object_item(item, #name))) { *error_msg = #name " error"; return 0; }
#define JSON_CHECK_STRING_MATCHES(name, rule) if (!ks_json_check_string_matches(ks_json_get_object_item(item, #name), rule)) { *error_msg = #name " error"; return 0; }
#define JSON_CHECK_STRING_MATCHES_OPTIONAL(name, rule) if (ks_json_get_object_item(item, #name) && !ks_json_check_string_matches(ks_json_get_object_item(item, #name), rule)) { *error_msg = #name " error"; return 0; }

#define JSON_CHECK_BOOLEAN(name) if (!ks_json_get_object_item(item, #name) || !ks_json_type_is_bool(ks_json_get_object_item(item, #name))) { *error_msg = #name " error"; return 0; }
#define JSON_CHECK_BOOLEAN_OPTIONAL(name) if (ks_json_get_object_item(item, #name) && !ks_json_type_is_bool(ks_json_get_object_item(item, #name))) { *error_msg = #name " error"; return 0; }

#define JSON_CHECK_END return 1; }

KS_DECLARE(int) ks_json_check_object(ks_json_t *json, const char *item_names);

KS_DECLARE(int) ks_json_check_array_items(ks_json_t *item, ks_json_check_function check, const char **error_msg);
KS_DECLARE(int) ks_json_check_is_any(ks_json_t *item);
KS_DECLARE(int) ks_json_check_is_array(ks_json_t *item);

KS_DECLARE(int) ks_json_check_number_is_any(ks_json_t *item);
KS_DECLARE(int) ks_json_check_number_is_8_bit_unsigned(ks_json_t *item);
KS_DECLARE(int) ks_json_check_number_is_not_negative(ks_json_t* item);
KS_DECLARE(int) ks_json_check_number_is_positive(ks_json_t* item);
KS_DECLARE(int) ks_json_check_number_is_positive_or_neg_one(ks_json_t* item);
KS_DECLARE(int) ks_json_check_number_is_decimal_between_zero_and_one(ks_json_t* item);

KS_DECLARE(int) ks_json_check_string_matches(ks_json_t *item, const char *rule);
KS_DECLARE(int) ks_json_check_string_is_not_negative(ks_json_t* item);
KS_DECLARE(int) ks_json_check_string_is_positive(ks_json_t* item);
KS_DECLARE(int) ks_json_check_string_is_positive_or_neg_one(ks_json_t* item);
KS_DECLARE(int) ks_json_check_string_is_decimal_between_zero_and_one(ks_json_t* item);
KS_DECLARE(int) ks_json_check_string_is_any(ks_json_t* item);
KS_DECLARE(int) ks_json_check_string_is_dtmf_digit(ks_json_t* item);
KS_DECLARE(int) ks_json_check_string_is_uuid(ks_json_t* item);
KS_DECLARE(int) ks_json_check_string_is_e164(ks_json_t* item);
KS_DECLARE(int) ks_json_check_string_is_any_nullable(ks_json_t *item);
KS_DECLARE(int) ks_json_check_string_is_any_or_empty(ks_json_t *item);

KS_DECLARE(int) ks_json_check_string_starts_with(ks_json_t *item, const char *match);
KS_DECLARE(int) ks_json_check_string_ends_with(ks_json_t *item, const char *match);

#endif
