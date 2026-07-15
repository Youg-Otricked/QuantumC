	.file	"master_module"
	.globaltype	__stack_pointer, i32
	.functype	qc_malloc (i64) -> (i32)
	.functype	malloc (i64) -> (i32)
	.functype	qc_free (i32) -> ()
	.functype	free (i32) -> ()
	.functype	qc_realloc (i32, i64) -> (i32)
	.functype	realloc (i32, i64) -> (i32)
	.functype	qc_calloc (i64, i64) -> (i32)
	.functype	calloc (i64, i64) -> (i32)
	.functype	qc_fmt_int (i64, i32, i32, i32) -> (i32)
	.functype	snprintf (i32, i64, i32, i32) -> (i32)
	.functype	qc_flush () -> ()
	.functype	fflush (i32) -> (i32)
	.functype	qc_fmt_unsigned_int (i64, i32) -> (i32)
	.functype	qc_fmt_float (f64, i32, i32, i32) -> (i32)
	.functype	qc_fmt_double (f64, i32, i32, i32) -> (i32)
	.functype	qc_fmt_scientific (f64, i32, i32, i32) -> (i32)
	.functype	qc_fmt_char (i32, i32, i32) -> (i32)
	.functype	qc_fmt_string (i32, i32, i32) -> (i32)
	.functype	qc_fmt_hex (i64, i32, i32) -> (i32)
	.functype	qc_fmt_octal (i64, i32, i32) -> (i32)
	.functype	qc_fmt_bool (i32, i32, i32) -> (i32)
	.functype	qc_fmt_qbool (i32, i32, i32) -> (i32)
	.functype	qc_fmt_ptr (i32, i32, i32) -> (i32)
	.functype	strdup (i32) -> (i32)
	.functype	qc_powi_i32 (i32, i32) -> (i32)
	.functype	qc_print_ptr (i32) -> ()
	.functype	printf (i32, i32) -> (i32)
	.functype	qc_string_concat (i32, i32) -> (i32)
	.functype	strlen (i32) -> (i64)
	.functype	qc_string_eq (i32, i32) -> (i32)
	.functype	strcmp (i32, i32) -> (i32)
	.functype	qc_qand (i32, i32) -> (i32)
	.functype	qc_qor (i32, i32) -> (i32)
	.functype	qc_qxor (i32, i32) -> (i32)
	.functype	qc_qnot (i32) -> (i32)
	.functype	qc_qand_collapse (i32, i32) -> (i32)
	.functype	qc_qor_collapse (i32, i32) -> (i32)
	.functype	qc_to_string_int (i32) -> (i32)
	.functype	qc_to_string_float (f32) -> (i32)
	.functype	qc_to_string_long_int (i64) -> (i32)
	.functype	qc_to_string_short_int (i32) -> (i32)
	.functype	qc_to_int_from_float (f32) -> (i32)
	.functype	qc_to_int_from_double (f64) -> (i32)
	.functype	qc_to_int_from_char (i32) -> (i32)
	.functype	qc_to_float_from_double (f64) -> (f32)
	.functype	qc_to_float_from_bool (i32) -> (f32)
	.functype	qc_to_double_from_float (f32) -> (f64)
	.functype	qc_to_double_from_bool (i32) -> (f64)
	.functype	qc_to_bool_from_int (i32) -> (i32)
	.functype	qc_to_bool_from_float (f32) -> (i32)
	.functype	qc_to_bool_from_double (f64) -> (i32)
	.functype	qc_to_char_from_int (i32) -> (i32)
	.functype	qc_to_string_double (f64) -> (i32)
	.functype	qc_to_string_bool (i32) -> (i32)
	.functype	qc_to_string_qbool (i32) -> (i32)
	.functype	qc_to_string_char (i32) -> (i32)
	.functype	qc_print_string (i32) -> ()
	.functype	fputs (i32, i32) -> (i32)
	.functype	qc_print_int (i32) -> ()
	.functype	qc_print_double (f64) -> ()
	.functype	qc_print_char (i32) -> ()
	.functype	putc (i32, i32) -> (i32)
	.functype	qc_time () -> (i32)
	.functype	time (i32) -> (i64)
	.functype	qc_seed (i32) -> ()
	.functype	srand (i32) -> ()
	.functype	qc_random_float () -> (f32)
	.functype	rand () -> (i32)
	.functype	qc_random_int (i32) -> (i32)
	.functype	qc_random_range (i32, i32) -> (i32)
	.functype	qc_len (i32) -> (i32)
	.functype	qc_to_lower (i32) -> (i32)
	.functype	tolower (i32) -> (i32)
	.functype	qc_to_upper (i32) -> (i32)
	.functype	toupper (i32) -> (i32)
	.functype	qc_substring (i32, i32, i32) -> (i32)
	.functype	qc_contains (i32, i32) -> (i32)
	.functype	strstr (i32, i32) -> (i32)
	.functype	qc_startswith (i32, i32) -> (i32)
	.functype	strncmp (i32, i32, i64) -> (i32)
	.functype	qc_endswith (i32, i32) -> (i32)
	.functype	qc_print_float (f32) -> ()
	.functype	qc_to_bool_from_string (i32) -> (i32)
	.functype	qc_to_qbool_from_string (i32) -> (i32)
	.functype	qc_qin () -> (i32)
	.functype	__isoc23_scanf (i32, i32) -> (i32)
	.functype	qc_print_bool (i32) -> ()
	.functype	qc_trim (i32) -> (i32)
	.functype	isspace (i32) -> (i32)
	.functype	qc_replace (i32, i32, i32) -> (i32)
	.functype	strcpy (i32, i32) -> (i32)
	.functype	qc_to_int_from_string (i32) -> (i32)
	.functype	__isoc23_strtol (i32, i32, i32) -> (i64)
	.functype	qc_to_short_int_from_string (i32) -> (i32)
	.functype	qc_to_long_int_from_string (i32) -> (i64)
	.functype	__isoc23_strtoll (i32, i32, i32) -> (i64)
	.functype	qc_to_addr_t_from_string (i32) -> (i64)
	.functype	__isoc23_strtoull (i32, i32, i32) -> (i64)
	.functype	qc_to_float_from_string (i32) -> (f32)
	.functype	strtod (i32, i32) -> (f64)
	.functype	qc_to_double_from_string (i32) -> (f64)
	.functype	qc_to_char_from_string (i32) -> (i32)
	.functype	qc_to_int_from_bool (i32) -> (i32)
	.functype	qc_to_float_from_int (i32) -> (f32)
	.functype	qc_to_double_from_int (i32) -> (f64)
	.functype	qc_print (i32) -> ()
	.functype	qc_println (i32) -> ()
	.functype	puts (i32) -> (i32)
	.functype	qc_print_array_int (i32, i32) -> ()
	.functype	qc_print_array_float (i32, i32) -> ()
	.functype	qc_print_array_double (i32, i32) -> ()
	.functype	qc_print_array_string (i32, i32) -> ()
	.functype	qc_print_array_char (i32, i32) -> ()
	.functype	qc_print_array_bool (i32, i32) -> ()
	.functype	qc_print_array_qbool (i32, i32) -> ()
	.functype	qc_sizeof_type (i32) -> (i32)
	.functype	qc_array_to_string_recursive (i32, i32, i32, i32) -> (i32)
	.functype	qc_print_array_recursive (i32, i32, i32, i32) -> ()
	.functype	qc_create_jagged_array (i32, i32, i32) -> (i32)
	.functype	qc_set_jagged_element (i32, i32, i32, i32) -> ()
	.functype	qc_free_jagged_array (i32) -> ()
	.functype	qc_print_jagged_array_recursive (i32) -> ()
	.functype	qc_jagged_array_get (i32, i32, i32) -> (i32)
	.functype	qc_create_leaf_row (i32, i32) -> (i32)
	.functype	qc_set_leaf_element (i32, i32, i32, i32) -> ()
	.functype	qc_stringify_jagged_helper (i32, i32, i32, i32, i32) -> ()
	.functype	qc_jagged_to_string (i32) -> (i32)
	.functype	qc_create_list (i32) -> (i32)
	.functype	qc_list_push (i32, i32, i32) -> ()
	.functype	qc_list_set (i32, i32, i32) -> ()
	.functype	qc_list_get (i32, i32) -> (i32)
	.functype	qc_list_pop (i32) -> (i32)
	.functype	qc_list_length (i32) -> (i32)
	.functype	qc_create_map (i32, i32) -> (i32)
	.functype	qc_compare_keys (i32, i32, i32) -> (i32)
	.functype	qc_map_set (i32, i32, i32) -> ()
	.functype	qc_map_get (i32, i32) -> (i32)
	.functype	qc_map_has (i32, i32) -> (i32)
	.functype	qc_map_remove (i32, i32) -> ()
	.functype	qc_print_map (i32) -> ()
	.functype	qc_map_to_string (i32) -> (i32)
	.functype	qc_map_size (i32) -> (i32)
	.functype	qc_map_keys (i32) -> (i32)
	.functype	qc_list_to_string (i32) -> (i32)
	.functype	qc_fopen (i32, i32) -> (i32)
	.functype	fopen (i32, i32) -> (i32)
	.functype	qc_fclose (i32) -> ()
	.functype	fclose (i32) -> (i32)
	.functype	qc_fread (i32) -> (i32)
	.functype	fgets (i32, i32, i32) -> (i32)
	.functype	qc_fwrite (i32, i32) -> ()
	.functype	fputc (i32, i32) -> (i32)
	.functype	qc_variadic_is_empty (i32) -> (i32)
	.functype	qc_variadic_next (i32) -> (i32)
	.functype	__user_entry () -> (i32)
	.functype	__original_main () -> (i32)
	.functype	main (i32, i32) -> (i32)
	.section	.text.qc_malloc,"",@
	.type	qc_malloc,@function             # -- Begin function qc_malloc
qc_malloc:                              # @qc_malloc
	.functype	qc_malloc (i64) -> (i32)
# %bb.0:
	local.get	0
	call	malloc
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_free,"",@
	.type	qc_free,@function               # -- Begin function qc_free
qc_free:                                # @qc_free
	.functype	qc_free (i32) -> ()
# %bb.0:
	local.get	0
	call	free
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_realloc,"",@
	.type	qc_realloc,@function            # -- Begin function qc_realloc
qc_realloc:                             # @qc_realloc
	.functype	qc_realloc (i32, i64) -> (i32)
# %bb.0:
	local.get	0
	local.get	1
	call	realloc
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_calloc,"",@
	.type	qc_calloc,@function             # -- Begin function qc_calloc
qc_calloc:                              # @qc_calloc
	.functype	qc_calloc (i64, i64) -> (i32)
# %bb.0:
	local.get	0
	local.get	1
	call	calloc
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_int,"",@
	.type	qc_fmt_int,@function            # -- Begin function qc_fmt_int
qc_fmt_int:                             # @qc_fmt_int
	.functype	qc_fmt_int (i64, i32, i32, i32) -> (i32)
	.local  	i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	112
	i32.sub 
	local.tee	4
	global.set	__stack_pointer
	block   	
	block   	
	local.get	2
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label1
# %bb.1:
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label2
# %bb.2:
	local.get	4
	local.get	2
	i32.store	40
	local.get	4
	local.get	1
	i32.store	36
	local.get	4
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	3
	i32.select
	i32.store	32
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str
	local.get	4
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	2                               # 2: down to label0
.LBB4_3:
	end_block                               # label2:
	local.get	4
	local.get	2
	i32.store	48
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.3
	local.get	4
	i32.const	48
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label0
.LBB4_4:
	end_block                               # label1:
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label3
# %bb.5:
	local.get	4
	local.get	1
	i32.store	68
	local.get	4
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	3
	i32.select
	i32.store	64
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.4
	local.get	4
	i32.const	64
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label0
.LBB4_6:
	end_block                               # label3:
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.5
	i32.const	0
	call	snprintf
	drop
.LBB4_7:
	end_block                               # label0:
	local.get	4
	local.get	0
	i64.store	16
	block   	
	i32.const	0
	i64.const	0
	local.get	4
	i32.const	80
	i32.add 
	local.get	4
	i32.const	16
	i32.add 
	call	snprintf
	i32.const	1
	i32.add 
	i64.extend_i32_s
	local.tee	5
	call	malloc
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label4
# %bb.8:
	local.get	4
	local.get	0
	i64.store	0
	local.get	2
	local.get	5
	local.get	4
	i32.const	80
	i32.add 
	local.get	4
	call	snprintf
	drop
.LBB4_9:
	end_block                               # label4:
	local.get	4
	i32.const	112
	i32.add 
	global.set	__stack_pointer
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_flush,"",@
	.type	qc_flush,@function              # -- Begin function qc_flush
qc_flush:                               # @qc_flush
	.functype	qc_flush () -> ()
# %bb.0:
	i32.const	0
	call	fflush
	drop
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_unsigned_int,"",@
	.type	qc_fmt_unsigned_int,@function   # -- Begin function qc_fmt_unsigned_int
qc_fmt_unsigned_int:                    # @qc_fmt_unsigned_int
	.functype	qc_fmt_unsigned_int (i64, i32) -> (i32)
	.local  	i32, i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	64
	i32.sub 
	local.tee	2
	global.set	__stack_pointer
	i32.const	0
	local.set	3
	local.get	2
	i32.const	32
	i32.add 
	i64.const	32
	i32.const	.L.str.6
	i32.const	.L.str.7
	local.get	1
	i32.select
	i32.const	0
	call	snprintf
	drop
	local.get	2
	local.get	0
	i64.store	16
	block   	
	i32.const	0
	i64.const	0
	local.get	2
	i32.const	32
	i32.add 
	local.get	2
	i32.const	16
	i32.add 
	call	snprintf
	local.tee	1
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label5
# %bb.1:
	local.get	1
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	4
	call	malloc
	local.tee	1
	i32.eqz
	br_if   	0                               # 0: down to label5
# %bb.2:
	local.get	2
	local.get	0
	i64.store	0
	local.get	1
	local.get	4
	local.get	2
	i32.const	32
	i32.add 
	local.get	2
	call	snprintf
	drop
	local.get	1
	local.set	3
.LBB6_3:
	end_block                               # label5:
	local.get	2
	i32.const	64
	i32.add 
	global.set	__stack_pointer
	local.get	3
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_float,"",@
	.type	qc_fmt_float,@function          # -- Begin function qc_fmt_float
qc_fmt_float:                           # @qc_fmt_float
	.functype	qc_fmt_float (f64, i32, i32, i32) -> (i32)
	.local  	i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	112
	i32.sub 
	local.tee	4
	global.set	__stack_pointer
	block   	
	block   	
	local.get	2
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label7
# %bb.1:
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label8
# %bb.2:
	local.get	4
	local.get	2
	i32.store	40
	local.get	4
	local.get	1
	i32.store	36
	local.get	4
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	3
	i32.select
	i32.store	32
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.8
	local.get	4
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	2                               # 2: down to label6
.LBB7_3:
	end_block                               # label8:
	local.get	4
	local.get	2
	i32.store	48
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.9
	local.get	4
	i32.const	48
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label6
.LBB7_4:
	end_block                               # label7:
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label9
# %bb.5:
	local.get	4
	local.get	1
	i32.store	68
	local.get	4
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	3
	i32.select
	i32.store	64
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.10
	local.get	4
	i32.const	64
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label6
.LBB7_6:
	end_block                               # label9:
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.11
	i32.const	0
	call	snprintf
	drop
.LBB7_7:
	end_block                               # label6:
	local.get	4
	local.get	0
	f64.store	16
	i32.const	0
	local.set	2
	block   	
	i32.const	0
	i64.const	0
	local.get	4
	i32.const	80
	i32.add 
	local.get	4
	i32.const	16
	i32.add 
	call	snprintf
	local.tee	1
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label10
# %bb.8:
	local.get	1
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	5
	call	malloc
	local.tee	1
	i32.eqz
	br_if   	0                               # 0: down to label10
# %bb.9:
	local.get	4
	local.get	0
	f64.store	0
	local.get	1
	local.get	5
	local.get	4
	i32.const	80
	i32.add 
	local.get	4
	call	snprintf
	drop
	local.get	1
	local.set	2
.LBB7_10:
	end_block                               # label10:
	local.get	4
	i32.const	112
	i32.add 
	global.set	__stack_pointer
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_double,"",@
	.type	qc_fmt_double,@function         # -- Begin function qc_fmt_double
qc_fmt_double:                          # @qc_fmt_double
	.functype	qc_fmt_double (f64, i32, i32, i32) -> (i32)
# %bb.0:
	local.get	0
	local.get	1
	local.get	2
	local.get	3
	call	qc_fmt_float
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_scientific,"",@
	.type	qc_fmt_scientific,@function     # -- Begin function qc_fmt_scientific
qc_fmt_scientific:                      # @qc_fmt_scientific
	.functype	qc_fmt_scientific (f64, i32, i32, i32) -> (i32)
	.local  	i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	112
	i32.sub 
	local.tee	4
	global.set	__stack_pointer
	block   	
	block   	
	local.get	2
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label12
# %bb.1:
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label13
# %bb.2:
	local.get	4
	local.get	2
	i32.store	40
	local.get	4
	local.get	1
	i32.store	36
	local.get	4
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	3
	i32.select
	i32.store	32
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.12
	local.get	4
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	2                               # 2: down to label11
.LBB9_3:
	end_block                               # label13:
	local.get	4
	local.get	2
	i32.store	48
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.13
	local.get	4
	i32.const	48
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label11
.LBB9_4:
	end_block                               # label12:
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label14
# %bb.5:
	local.get	4
	local.get	1
	i32.store	68
	local.get	4
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	3
	i32.select
	i32.store	64
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.14
	local.get	4
	i32.const	64
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label11
.LBB9_6:
	end_block                               # label14:
	local.get	4
	i32.const	80
	i32.add 
	i64.const	32
	i32.const	.L.str.15
	i32.const	0
	call	snprintf
	drop
.LBB9_7:
	end_block                               # label11:
	local.get	4
	local.get	0
	f64.store	16
	i32.const	0
	local.set	2
	block   	
	i32.const	0
	i64.const	0
	local.get	4
	i32.const	80
	i32.add 
	local.get	4
	i32.const	16
	i32.add 
	call	snprintf
	local.tee	1
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label15
# %bb.8:
	local.get	1
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	5
	call	malloc
	local.tee	1
	i32.eqz
	br_if   	0                               # 0: down to label15
# %bb.9:
	local.get	4
	local.get	0
	f64.store	0
	local.get	1
	local.get	5
	local.get	4
	i32.const	80
	i32.add 
	local.get	4
	call	snprintf
	drop
	local.get	1
	local.set	2
.LBB9_10:
	end_block                               # label15:
	local.get	4
	i32.const	112
	i32.add 
	global.set	__stack_pointer
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_char,"",@
	.type	qc_fmt_char,@function           # -- Begin function qc_fmt_char
qc_fmt_char:                            # @qc_fmt_char
	.functype	qc_fmt_char (i32, i32, i32) -> (i32)
	.local  	i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	64
	i32.sub 
	local.tee	3
	global.set	__stack_pointer
	block   	
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label17
# %bb.1:
	local.get	3
	local.get	1
	i32.store	36
	local.get	3
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	2
	i32.select
	i32.store	32
	local.get	3
	i32.const	48
	i32.add 
	i64.const	16
	i32.const	.L.str.16
	local.get	3
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label16
.LBB10_2:
	end_block                               # label17:
	local.get	3
	i32.const	48
	i32.add 
	i64.const	16
	i32.const	.L.str.17
	i32.const	0
	call	snprintf
	drop
.LBB10_3:
	end_block                               # label16:
	local.get	3
	local.get	0
	i32.store	16
	i32.const	0
	local.set	1
	block   	
	i32.const	0
	i64.const	0
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	i32.const	16
	i32.add 
	call	snprintf
	local.tee	2
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label18
# %bb.4:
	local.get	2
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	4
	call	malloc
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label18
# %bb.5:
	local.get	3
	local.get	0
	i32.store	0
	local.get	2
	local.get	4
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	call	snprintf
	drop
	local.get	2
	local.set	1
.LBB10_6:
	end_block                               # label18:
	local.get	3
	i32.const	64
	i32.add 
	global.set	__stack_pointer
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_string,"",@
	.type	qc_fmt_string,@function         # -- Begin function qc_fmt_string
qc_fmt_string:                          # @qc_fmt_string
	.functype	qc_fmt_string (i32, i32, i32) -> (i32)
	.local  	i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	64
	i32.sub 
	local.tee	3
	global.set	__stack_pointer
	local.get	0
	i32.const	.L.str.2
	local.get	0
	i32.select
	local.set	0
	block   	
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label20
# %bb.1:
	local.get	3
	local.get	1
	i32.store	36
	local.get	3
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	2
	i32.select
	i32.store	32
	local.get	3
	i32.const	48
	i32.add 
	i64.const	16
	i32.const	.L.str.18
	local.get	3
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label19
.LBB11_2:
	end_block                               # label20:
	local.get	3
	i32.const	48
	i32.add 
	i64.const	16
	i32.const	.L.str.19
	i32.const	0
	call	snprintf
	drop
.LBB11_3:
	end_block                               # label19:
	local.get	3
	local.get	0
	i32.store	16
	i32.const	0
	local.set	1
	block   	
	i32.const	0
	i64.const	0
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	i32.const	16
	i32.add 
	call	snprintf
	local.tee	2
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label21
# %bb.4:
	local.get	2
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	4
	call	malloc
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label21
# %bb.5:
	local.get	3
	local.get	0
	i32.store	0
	local.get	2
	local.get	4
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	call	snprintf
	drop
	local.get	2
	local.set	1
.LBB11_6:
	end_block                               # label21:
	local.get	3
	i32.const	64
	i32.add 
	global.set	__stack_pointer
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_hex,"",@
	.type	qc_fmt_hex,@function            # -- Begin function qc_fmt_hex
qc_fmt_hex:                             # @qc_fmt_hex
	.functype	qc_fmt_hex (i64, i32, i32) -> (i32)
	.local  	i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	80
	i32.sub 
	local.tee	3
	global.set	__stack_pointer
	block   	
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label23
# %bb.1:
	local.get	3
	local.get	1
	i32.store	36
	local.get	3
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	2
	i32.select
	i32.store	32
	local.get	3
	i32.const	48
	i32.add 
	i64.const	32
	i32.const	.L.str.20
	local.get	3
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label22
.LBB12_2:
	end_block                               # label23:
	local.get	3
	i32.const	48
	i32.add 
	i64.const	32
	i32.const	.L.str.21
	i32.const	0
	call	snprintf
	drop
.LBB12_3:
	end_block                               # label22:
	local.get	3
	local.get	0
	i64.store	16
	block   	
	i32.const	0
	i64.const	0
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	i32.const	16
	i32.add 
	call	snprintf
	i32.const	1
	i32.add 
	i64.extend_i32_s
	local.tee	4
	call	malloc
	local.tee	1
	i32.eqz
	br_if   	0                               # 0: down to label24
# %bb.4:
	local.get	3
	local.get	0
	i64.store	0
	local.get	1
	local.get	4
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	call	snprintf
	drop
.LBB12_5:
	end_block                               # label24:
	local.get	3
	i32.const	80
	i32.add 
	global.set	__stack_pointer
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_octal,"",@
	.type	qc_fmt_octal,@function          # -- Begin function qc_fmt_octal
qc_fmt_octal:                           # @qc_fmt_octal
	.functype	qc_fmt_octal (i64, i32, i32) -> (i32)
	.local  	i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	80
	i32.sub 
	local.tee	3
	global.set	__stack_pointer
	block   	
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label26
# %bb.1:
	local.get	3
	local.get	1
	i32.store	36
	local.get	3
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	2
	i32.select
	i32.store	32
	local.get	3
	i32.const	48
	i32.add 
	i64.const	32
	i32.const	.L.str.22
	local.get	3
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label25
.LBB13_2:
	end_block                               # label26:
	local.get	3
	i32.const	48
	i32.add 
	i64.const	32
	i32.const	.L.str.23
	i32.const	0
	call	snprintf
	drop
.LBB13_3:
	end_block                               # label25:
	local.get	3
	local.get	0
	i64.store	16
	block   	
	i32.const	0
	i64.const	0
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	i32.const	16
	i32.add 
	call	snprintf
	i32.const	1
	i32.add 
	i64.extend_i32_s
	local.tee	4
	call	malloc
	local.tee	1
	i32.eqz
	br_if   	0                               # 0: down to label27
# %bb.4:
	local.get	3
	local.get	0
	i64.store	0
	local.get	1
	local.get	4
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	call	snprintf
	drop
.LBB13_5:
	end_block                               # label27:
	local.get	3
	i32.const	80
	i32.add 
	global.set	__stack_pointer
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_bool,"",@
	.type	qc_fmt_bool,@function           # -- Begin function qc_fmt_bool
qc_fmt_bool:                            # @qc_fmt_bool
	.functype	qc_fmt_bool (i32, i32, i32) -> (i32)
	.local  	i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	64
	i32.sub 
	local.tee	3
	global.set	__stack_pointer
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.select
	local.set	0
	block   	
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label29
# %bb.1:
	local.get	3
	local.get	1
	i32.store	36
	local.get	3
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	2
	i32.select
	i32.store	32
	local.get	3
	i32.const	48
	i32.add 
	i64.const	16
	i32.const	.L.str.18
	local.get	3
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label28
.LBB14_2:
	end_block                               # label29:
	local.get	3
	i32.const	48
	i32.add 
	i64.const	16
	i32.const	.L.str.19
	i32.const	0
	call	snprintf
	drop
.LBB14_3:
	end_block                               # label28:
	local.get	3
	local.get	0
	i32.store	16
	i32.const	0
	local.set	1
	block   	
	i32.const	0
	i64.const	0
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	i32.const	16
	i32.add 
	call	snprintf
	local.tee	2
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label30
# %bb.4:
	local.get	2
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	4
	call	malloc
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label30
# %bb.5:
	local.get	3
	local.get	0
	i32.store	0
	local.get	2
	local.get	4
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	call	snprintf
	drop
	local.get	2
	local.set	1
.LBB14_6:
	end_block                               # label30:
	local.get	3
	i32.const	64
	i32.add 
	global.set	__stack_pointer
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_qbool,"",@
	.type	qc_fmt_qbool,@function          # -- Begin function qc_fmt_qbool
qc_fmt_qbool:                           # @qc_fmt_qbool
	.functype	qc_fmt_qbool (i32, i32, i32) -> (i32)
	.local  	i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	64
	i32.sub 
	local.tee	3
	global.set	__stack_pointer
	local.get	0
	i32.const	3
	i32.and 
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_print_array_qbool
	local.set	0
	block   	
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label32
# %bb.1:
	local.get	3
	local.get	1
	i32.store	36
	local.get	3
	i32.const	.L.str.1
	i32.const	.L.str.2
	local.get	2
	i32.select
	i32.store	32
	local.get	3
	i32.const	48
	i32.add 
	i64.const	16
	i32.const	.L.str.18
	local.get	3
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label31
.LBB15_2:
	end_block                               # label32:
	local.get	3
	i32.const	48
	i32.add 
	i64.const	16
	i32.const	.L.str.19
	i32.const	0
	call	snprintf
	drop
.LBB15_3:
	end_block                               # label31:
	local.get	3
	local.get	0
	i32.store	16
	i32.const	0
	local.set	1
	block   	
	i32.const	0
	i64.const	0
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	i32.const	16
	i32.add 
	call	snprintf
	local.tee	2
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label33
# %bb.4:
	local.get	2
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	4
	call	malloc
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label33
# %bb.5:
	local.get	3
	local.get	0
	i32.store	0
	local.get	2
	local.get	4
	local.get	3
	i32.const	48
	i32.add 
	local.get	3
	call	snprintf
	drop
	local.get	2
	local.set	1
.LBB15_6:
	end_block                               # label33:
	local.get	3
	i32.const	64
	i32.add 
	global.set	__stack_pointer
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fmt_ptr,"",@
	.type	qc_fmt_ptr,@function            # -- Begin function qc_fmt_ptr
qc_fmt_ptr:                             # @qc_fmt_ptr
	.functype	qc_fmt_ptr (i32, i32, i32) -> (i32)
	.local  	i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	112
	i32.sub 
	local.tee	3
	global.set	__stack_pointer
	block   	
	block   	
	local.get	2
	i32.eqz
	br_if   	0                               # 0: down to label35
# %bb.1:
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label35
# %bb.2:
	local.get	3
	local.get	1
	i32.store	0
	local.get	3
	local.get	0
	i64.extend_i32_u
	i64.store	8
	local.get	3
	i32.const	48
	i32.add 
	i64.const	64
	i32.const	.L.str.30
	local.get	3
	call	snprintf
	drop
	br      	1                               # 1: down to label34
.LBB16_3:
	end_block                               # label35:
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label36
# %bb.4:
	local.get	3
	local.get	0
	i32.store	20
	local.get	3
	local.get	1
	i32.store	16
	local.get	3
	i32.const	48
	i32.add 
	i64.const	64
	i32.const	.L.str.31
	local.get	3
	i32.const	16
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label34
.LBB16_5:
	end_block                               # label36:
	local.get	3
	local.get	0
	i32.store	32
	local.get	3
	i32.const	48
	i32.add 
	i64.const	64
	i32.const	.L.str.32
	local.get	3
	i32.const	32
	i32.add 
	call	snprintf
	drop
.LBB16_6:
	end_block                               # label34:
	local.get	3
	i32.const	48
	i32.add 
	call	strdup
	local.set	1
	local.get	3
	i32.const	112
	i32.add 
	global.set	__stack_pointer
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_powi_i32,"",@
	.type	qc_powi_i32,@function           # -- Begin function qc_powi_i32
qc_powi_i32:                            # @qc_powi_i32
	.functype	qc_powi_i32 (i32, i32) -> (i32)
	.local  	i32, i32
# %bb.0:
	i32.const	0
	local.set	2
	block   	
	local.get	1
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label37
# %bb.1:
	block   	
	local.get	1
	br_if   	0                               # 0: down to label38
# %bb.2:
	i32.const	1
	return
.LBB17_3:                               # %.preheader
	end_block                               # label38:
	i32.const	1
	local.set	2
.LBB17_4:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label39:
	local.get	0
	i32.const	1
	local.get	1
	i32.const	1
	i32.and 
	i32.select
	local.get	2
	i32.mul 
	local.set	2
	local.get	1
	i32.const	1
	i32.gt_u
	local.set	3
	local.get	0
	local.get	0
	i32.mul 
	local.set	0
	local.get	1
	i32.const	1
	i32.shr_u
	local.set	1
	local.get	3
	br_if   	0                               # 0: up to label39
.LBB17_5:
	end_loop
	end_block                               # label37:
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_ptr,"",@
	.type	qc_print_ptr,@function          # -- Begin function qc_print_ptr
qc_print_ptr:                           # @qc_print_ptr
	.functype	qc_print_ptr (i32) -> ()
	.local  	i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	local.get	0
	i32.store	0
	i32.const	.L.str.33
	local.get	1
	call	printf
	drop
	local.get	1
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_string_concat,"",@
	.type	qc_string_concat,@function      # -- Begin function qc_string_concat
qc_string_concat:                       # @qc_string_concat
	.functype	qc_string_concat (i32, i32) -> (i32)
	.local  	i64, i32, i64, i64, i32
# %bb.0:
	block   	
	local.get	0
	i32.const	.L.str.2
	local.get	0
	i32.select
	local.tee	0
	call	strlen
	local.tee	2
	local.get	1
	i32.const	.L.str.2
	local.get	1
	i32.select
	local.tee	3
	call	strlen
	local.tee	4
	i64.add 
	local.tee	5
	i64.const	1
	i64.add 
	call	malloc
	local.tee	1
	i32.eqz
	br_if   	0                               # 0: down to label40
# %bb.1:
	block   	
	local.get	2
	i32.wrap_i64
	local.tee	6
	i32.eqz
	br_if   	0                               # 0: down to label41
# %bb.2:
	local.get	1
	local.get	0
	local.get	6
	memory.copy	0, 0
.LBB19_3:
	end_block                               # label41:
	block   	
	local.get	4
	i32.wrap_i64
	local.tee	0
	i32.eqz
	br_if   	0                               # 0: down to label42
# %bb.4:
	local.get	1
	local.get	6
	i32.add 
	local.get	3
	local.get	0
	memory.copy	0, 0
.LBB19_5:
	end_block                               # label42:
	local.get	1
	local.get	5
	i32.wrap_i64
	i32.add 
	i32.const	0
	i32.store8	0
.LBB19_6:
	end_block                               # label40:
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_string_eq,"",@
	.type	qc_string_eq,@function          # -- Begin function qc_string_eq
qc_string_eq:                           # @qc_string_eq
	.functype	qc_string_eq (i32, i32) -> (i32)
	.local  	i32
# %bb.0:
	i32.const	0
	local.set	2
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label43
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label43
# %bb.2:
	local.get	0
	local.get	1
	call	strcmp
	i32.eqz
	local.set	2
.LBB20_3:
	end_block                               # label43:
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_qand,"",@
	.type	qc_qand,@function               # -- Begin function qc_qand
qc_qand:                                # @qc_qand
	.functype	qc_qand (i32, i32) -> (i32)
# %bb.0:
	i32.const	1
	i32.const	1
	i32.const	2
	i32.const	3
	local.get	1
	i32.const	2
	i32.eq  
	i32.select
	i32.const	3
	local.get	0
	i32.const	2
	i32.eq  
	i32.select
	local.get	1
	i32.const	2
	i32.lt_u
	i32.select
	local.get	0
	i32.const	2
	i32.lt_u
	i32.select
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_qor,"",@
	.type	qc_qor,@function                # -- Begin function qc_qor
qc_qor:                                 # @qc_qor
	.functype	qc_qor (i32, i32) -> (i32)
	.local  	i32
# %bb.0:
	block   	
	local.get	1
	local.get	0
	i32.or  
	br_if   	0                               # 0: down to label44
# %bb.1:
	i32.const	0
	return
.LBB22_2:
	end_block                               # label44:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label45
# %bb.3:
	local.get	1
	i32.const	1
	i32.ne  
	br_if   	0                               # 0: down to label45
# %bb.4:
	i32.const	1
	return
.LBB22_5:
	end_block                               # label45:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label46
# %bb.6:
	local.get	1
	i32.const	2
	i32.ne  
	br_if   	0                               # 0: down to label46
# %bb.7:
	i32.const	2
	return
.LBB22_8:
	end_block                               # label46:
	i32.const	1
	local.set	2
	block   	
	block   	
	local.get	0
	i32.const	1
	i32.ne  
	br_if   	0                               # 0: down to label48
# %bb.9:
	local.get	1
	i32.const	2
	i32.lt_u
	br_if   	1                               # 1: down to label47
.LBB22_10:
	end_block                               # label48:
	i32.const	2
	local.set	2
	block   	
	local.get	0
	i32.const	2
	i32.ne  
	br_if   	0                               # 0: down to label49
# %bb.11:
	local.get	1
	i32.eqz
	br_if   	1                               # 1: down to label47
.LBB22_12:
	end_block                               # label49:
	i32.const	2
	i32.const	3
	local.get	1
	i32.const	2
	i32.eq  
	i32.select
	i32.const	3
	local.get	0
	i32.const	2
	i32.eq  
	i32.select
	local.set	2
.LBB22_13:
	end_block                               # label47:
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_qxor,"",@
	.type	qc_qxor,@function               # -- Begin function qc_qxor
qc_qxor:                                # @qc_qxor
	.functype	qc_qxor (i32, i32) -> (i32)
# %bb.0:
	block   	
	local.get	1
	local.get	0
	i32.or  
	i32.const	2
	i32.ge_u
	br_if   	0                               # 0: down to label50
# %bb.1:
	i32.const	0
	return
.LBB23_2:
	end_block                               # label50:
	block   	
	local.get	0
	i32.const	2
	i32.lt_u
	local.get	1
	i32.const	2
	i32.lt_u
	i32.xor 
	i32.eqz
	br_if   	0                               # 0: down to label51
# %bb.3:
	i32.const	3
	return
.LBB23_4:
	end_block                               # label51:
	i32.const	1
	i32.const	3
	local.get	1
	i32.const	2
	i32.eq  
	i32.select
	i32.const	3
	local.get	0
	i32.const	2
	i32.eq  
	i32.select
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_qnot,"",@
	.type	qc_qnot,@function               # -- Begin function qc_qnot
qc_qnot:                                # @qc_qnot
	.functype	qc_qnot (i32) -> (i32)
# %bb.0:
	i32.const	3
	local.get	0
	i32.sub 
	i32.const	255
	i32.and 
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_qand_collapse,"",@
	.type	qc_qand_collapse,@function      # -- Begin function qc_qand_collapse
qc_qand_collapse:                       # @qc_qand_collapse
	.functype	qc_qand_collapse (i32, i32) -> (i32)
# %bb.0:
	local.get	0
	local.get	1
	i32.and 
	i32.const	2
	i32.and 
	i32.const	1
	i32.shr_u
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_qor_collapse,"",@
	.type	qc_qor_collapse,@function       # -- Begin function qc_qor_collapse
qc_qor_collapse:                        # @qc_qor_collapse
	.functype	qc_qor_collapse (i32, i32) -> (i32)
# %bb.0:
	local.get	1
	local.get	0
	i32.or  
	i32.const	2
	i32.and 
	i32.const	1
	i32.shr_u
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_string_int,"",@
	.type	qc_to_string_int,@function      # -- Begin function qc_to_string_int
qc_to_string_int:                       # @qc_to_string_int
	.functype	qc_to_string_int (i32) -> (i32)
	.local  	i32, i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	48
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	local.get	0
	i32.store	0
	i32.const	0
	local.set	0
	block   	
	local.get	1
	i32.const	16
	i32.add 
	i64.const	32
	i32.const	.L.str.34
	local.get	1
	call	snprintf
	local.tee	2
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label52
# %bb.1:
	local.get	2
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	3
	call	malloc
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label52
# %bb.2:
	block   	
	local.get	3
	i32.wrap_i64
	local.tee	0
	i32.eqz
	br_if   	0                               # 0: down to label53
# %bb.3:
	local.get	2
	local.get	1
	i32.const	16
	i32.add 
	local.get	0
	memory.copy	0, 0
.LBB27_4:
	end_block                               # label53:
	local.get	2
	local.set	0
.LBB27_5:
	end_block                               # label52:
	local.get	1
	i32.const	48
	i32.add 
	global.set	__stack_pointer
	local.get	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_string_float,"",@
	.type	qc_to_string_float,@function    # -- Begin function qc_to_string_float
qc_to_string_float:                     # @qc_to_string_float
	.functype	qc_to_string_float (f32) -> (i32)
	.local  	i32, i32, i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	80
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	local.get	0
	f64.promote_f32
	f64.store	0
	i32.const	0
	local.set	2
	block   	
	local.get	1
	i32.const	16
	i32.add 
	i64.const	64
	i32.const	.L.str.35
	local.get	1
	call	snprintf
	local.tee	3
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label54
# %bb.1:
	local.get	3
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	4
	call	malloc
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label54
# %bb.2:
	block   	
	local.get	4
	i32.wrap_i64
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label55
# %bb.3:
	local.get	3
	local.get	1
	i32.const	16
	i32.add 
	local.get	2
	memory.copy	0, 0
.LBB28_4:
	end_block                               # label55:
	local.get	3
	local.set	2
.LBB28_5:
	end_block                               # label54:
	local.get	1
	i32.const	80
	i32.add 
	global.set	__stack_pointer
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_string_long_int,"",@
	.type	qc_to_string_long_int,@function # -- Begin function qc_to_string_long_int
qc_to_string_long_int:                  # @qc_to_string_long_int
	.functype	qc_to_string_long_int (i64) -> (i32)
	.local  	i32, i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	48
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	local.get	0
	i64.store	0
	i32.const	0
	local.set	2
	block   	
	local.get	1
	i32.const	16
	i32.add 
	i64.const	32
	i32.const	.L.str.36
	local.get	1
	call	snprintf
	local.tee	3
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label56
# %bb.1:
	local.get	3
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	0
	call	malloc
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label56
# %bb.2:
	block   	
	local.get	0
	i32.wrap_i64
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label57
# %bb.3:
	local.get	3
	local.get	1
	i32.const	16
	i32.add 
	local.get	2
	memory.copy	0, 0
.LBB29_4:
	end_block                               # label57:
	local.get	3
	local.set	2
.LBB29_5:
	end_block                               # label56:
	local.get	1
	i32.const	48
	i32.add 
	global.set	__stack_pointer
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_string_short_int,"",@
	.type	qc_to_string_short_int,@function # -- Begin function qc_to_string_short_int
qc_to_string_short_int:                 # @qc_to_string_short_int
	.functype	qc_to_string_short_int (i32) -> (i32)
	.local  	i32, i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	80
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	local.get	0
	i32.store	0
	i32.const	0
	local.set	0
	block   	
	local.get	1
	i32.const	16
	i32.add 
	i64.const	64
	i32.const	.L.str.37
	local.get	1
	call	snprintf
	local.tee	2
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label58
# %bb.1:
	local.get	2
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	3
	call	malloc
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label58
# %bb.2:
	block   	
	local.get	3
	i32.wrap_i64
	local.tee	0
	i32.eqz
	br_if   	0                               # 0: down to label59
# %bb.3:
	local.get	2
	local.get	1
	i32.const	16
	i32.add 
	local.get	0
	memory.copy	0, 0
.LBB30_4:
	end_block                               # label59:
	local.get	2
	local.set	0
.LBB30_5:
	end_block                               # label58:
	local.get	1
	i32.const	80
	i32.add 
	global.set	__stack_pointer
	local.get	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_int_from_float,"",@
	.type	qc_to_int_from_float,@function  # -- Begin function qc_to_int_from_float
qc_to_int_from_float:                   # @qc_to_int_from_float
	.functype	qc_to_int_from_float (f32) -> (i32)
# %bb.0:
	local.get	0
	i32.trunc_sat_f32_s
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_int_from_double,"",@
	.type	qc_to_int_from_double,@function # -- Begin function qc_to_int_from_double
qc_to_int_from_double:                  # @qc_to_int_from_double
	.functype	qc_to_int_from_double (f64) -> (i32)
# %bb.0:
	local.get	0
	i32.trunc_sat_f64_s
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_int_from_char,"",@
	.type	qc_to_int_from_char,@function   # -- Begin function qc_to_int_from_char
qc_to_int_from_char:                    # @qc_to_int_from_char
	.functype	qc_to_int_from_char (i32) -> (i32)
# %bb.0:
	local.get	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_float_from_double,"",@
	.type	qc_to_float_from_double,@function # -- Begin function qc_to_float_from_double
qc_to_float_from_double:                # @qc_to_float_from_double
	.functype	qc_to_float_from_double (f64) -> (f32)
# %bb.0:
	local.get	0
	f32.demote_f64
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_float_from_bool,"",@
	.type	qc_to_float_from_bool,@function # -- Begin function qc_to_float_from_bool
qc_to_float_from_bool:                  # @qc_to_float_from_bool
	.functype	qc_to_float_from_bool (i32) -> (f32)
# %bb.0:
	f32.const	0x1p0
	f32.const	0x0p0
	local.get	0
	f32.select
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_double_from_float,"",@
	.type	qc_to_double_from_float,@function # -- Begin function qc_to_double_from_float
qc_to_double_from_float:                # @qc_to_double_from_float
	.functype	qc_to_double_from_float (f32) -> (f64)
# %bb.0:
	local.get	0
	f64.promote_f32
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_double_from_bool,"",@
	.type	qc_to_double_from_bool,@function # -- Begin function qc_to_double_from_bool
qc_to_double_from_bool:                 # @qc_to_double_from_bool
	.functype	qc_to_double_from_bool (i32) -> (f64)
# %bb.0:
	f64.const	0x1p0
	f64.const	0x0p0
	local.get	0
	f64.select
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_bool_from_int,"",@
	.type	qc_to_bool_from_int,@function   # -- Begin function qc_to_bool_from_int
qc_to_bool_from_int:                    # @qc_to_bool_from_int
	.functype	qc_to_bool_from_int (i32) -> (i32)
# %bb.0:
	local.get	0
	i32.const	0
	i32.ne  
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_bool_from_float,"",@
	.type	qc_to_bool_from_float,@function # -- Begin function qc_to_bool_from_float
qc_to_bool_from_float:                  # @qc_to_bool_from_float
	.functype	qc_to_bool_from_float (f32) -> (i32)
# %bb.0:
	local.get	0
	f32.const	0x0p0
	f32.ne  
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_bool_from_double,"",@
	.type	qc_to_bool_from_double,@function # -- Begin function qc_to_bool_from_double
qc_to_bool_from_double:                 # @qc_to_bool_from_double
	.functype	qc_to_bool_from_double (f64) -> (i32)
# %bb.0:
	local.get	0
	f64.const	0x0p0
	f64.ne  
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_char_from_int,"",@
	.type	qc_to_char_from_int,@function   # -- Begin function qc_to_char_from_int
qc_to_char_from_int:                    # @qc_to_char_from_int
	.functype	qc_to_char_from_int (i32) -> (i32)
# %bb.0:
	local.get	0
	i32.extend8_s
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_string_double,"",@
	.type	qc_to_string_double,@function   # -- Begin function qc_to_string_double
qc_to_string_double:                    # @qc_to_string_double
	.functype	qc_to_string_double (f64) -> (i32)
	.local  	i32, i32, i32, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	80
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	local.get	0
	f64.store	0
	i32.const	0
	local.set	2
	block   	
	local.get	1
	i32.const	16
	i32.add 
	i64.const	64
	i32.const	.L.str.35
	local.get	1
	call	snprintf
	local.tee	3
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label60
# %bb.1:
	local.get	3
	i32.const	1
	i32.add 
	i64.extend_i32_u
	local.tee	4
	call	malloc
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label60
# %bb.2:
	block   	
	local.get	4
	i32.wrap_i64
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label61
# %bb.3:
	local.get	3
	local.get	1
	i32.const	16
	i32.add 
	local.get	2
	memory.copy	0, 0
.LBB42_4:
	end_block                               # label61:
	local.get	3
	local.set	2
.LBB42_5:
	end_block                               # label60:
	local.get	1
	i32.const	80
	i32.add 
	global.set	__stack_pointer
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_string_bool,"",@
	.type	qc_to_string_bool,@function     # -- Begin function qc_to_string_bool
qc_to_string_bool:                      # @qc_to_string_bool
	.functype	qc_to_string_bool (i32) -> (i32)
	.local  	i64, i32, i32
# %bb.0:
	block   	
	i64.const	5
	i64.const	6
	local.get	0
	i64.select
	local.tee	1
	call	malloc
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label62
# %bb.1:
	local.get	1
	i32.wrap_i64
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label62
# %bb.2:
	local.get	2
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.select
	local.get	3
	memory.copy	0, 0
.LBB43_3:
	end_block                               # label62:
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_string_qbool,"",@
	.type	qc_to_string_qbool,@function    # -- Begin function qc_to_string_qbool
qc_to_string_qbool:                     # @qc_to_string_qbool
	.functype	qc_to_string_qbool (i32) -> (i32)
	.local  	i32, i64, i32
# %bb.0:
	block   	
	local.get	0
	i32.const	3
	i32.and 
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_print_array_qbool
	local.tee	1
	call	strlen
	i64.const	1
	i64.add 
	local.tee	2
	call	malloc
	local.tee	0
	i32.eqz
	br_if   	0                               # 0: down to label63
# %bb.1:
	local.get	2
	i32.wrap_i64
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label63
# %bb.2:
	local.get	0
	local.get	1
	local.get	3
	memory.copy	0, 0
.LBB44_3:
	end_block                               # label63:
	local.get	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_string_char,"",@
	.type	qc_to_string_char,@function     # -- Begin function qc_to_string_char
qc_to_string_char:                      # @qc_to_string_char
	.functype	qc_to_string_char (i32) -> (i32)
	.local  	i32
# %bb.0:
	block   	
	i64.const	2
	call	malloc
	local.tee	1
	i32.eqz
	br_if   	0                               # 0: down to label64
# %bb.1:
	local.get	1
	i32.const	0
	i32.store8	1
	local.get	1
	local.get	0
	i32.store8	0
.LBB45_2:
	end_block                               # label64:
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_string,"",@
	.type	qc_print_string,@function       # -- Begin function qc_print_string
qc_print_string:                        # @qc_print_string
	.functype	qc_print_string (i32) -> ()
# %bb.0:
	local.get	0
	i32.const	.L.str.2
	local.get	0
	i32.select
	i32.const	0
	i32.load	stdout
	call	fputs
	drop
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_int,"",@
	.type	qc_print_int,@function          # -- Begin function qc_print_int
qc_print_int:                           # @qc_print_int
	.functype	qc_print_int (i32) -> ()
	.local  	i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	local.get	0
	i32.store	0
	i32.const	.L.str.34
	local.get	1
	call	printf
	drop
	local.get	1
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_double,"",@
	.type	qc_print_double,@function       # -- Begin function qc_print_double
qc_print_double:                        # @qc_print_double
	.functype	qc_print_double (f64) -> ()
	.local  	i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	local.get	0
	f64.store	0
	i32.const	.L.str.35
	local.get	1
	call	printf
	drop
	local.get	1
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_char,"",@
	.type	qc_print_char,@function         # -- Begin function qc_print_char
qc_print_char:                          # @qc_print_char
	.functype	qc_print_char (i32) -> ()
# %bb.0:
	local.get	0
	i32.const	255
	i32.and 
	i32.const	0
	i32.load	stdout
	call	putc
	drop
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_time,"",@
	.type	qc_time,@function               # -- Begin function qc_time
qc_time:                                # @qc_time
	.functype	qc_time () -> (i32)
# %bb.0:
	i32.const	0
	call	time
	i32.wrap_i64
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_seed,"",@
	.type	qc_seed,@function               # -- Begin function qc_seed
qc_seed:                                # @qc_seed
	.functype	qc_seed (i32) -> ()
# %bb.0:
	local.get	0
	call	srand
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_random_float,"",@
	.type	qc_random_float,@function       # -- Begin function qc_random_float
qc_random_float:                        # @qc_random_float
	.functype	qc_random_float () -> (f32)
# %bb.0:
	call	rand
	f32.convert_i32_s
	f32.const	0x1p-31
	f32.mul 
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_random_int,"",@
	.type	qc_random_int,@function         # -- Begin function qc_random_int
qc_random_int:                          # @qc_random_int
	.functype	qc_random_int (i32) -> (i32)
# %bb.0:
	call	rand
	local.get	0
	i32.rem_s
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_random_range,"",@
	.type	qc_random_range,@function       # -- Begin function qc_random_range
qc_random_range:                        # @qc_random_range
	.functype	qc_random_range (i32, i32) -> (i32)
# %bb.0:
	call	rand
	local.get	1
	local.get	0
	i32.sub 
	i32.rem_s
	local.get	0
	i32.add 
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_len,"",@
	.type	qc_len,@function                # -- Begin function qc_len
qc_len:                                 # @qc_len
	.functype	qc_len (i32) -> (i32)
# %bb.0:
	local.get	0
	call	strlen
	i32.wrap_i64
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_lower,"",@
	.type	qc_to_lower,@function           # -- Begin function qc_to_lower
qc_to_lower:                            # @qc_to_lower
	.functype	qc_to_lower (i32) -> (i32)
	.local  	i32, i64, i32, i64
# %bb.0:
	i32.const	0
	local.set	1
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label65
# %bb.1:
	local.get	0
	call	strlen
	local.tee	2
	i64.const	1
	i64.add 
	call	malloc
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label65
# %bb.2:
	block   	
	local.get	2
	i64.eqz
	br_if   	0                               # 0: down to label66
# %bb.3:
	local.get	3
	local.set	1
	local.get	2
	local.set	4
.LBB56_4:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label67:
	local.get	1
	local.get	0
	i32.load8_u	0
	call	tolower
	i32.store8	0
	local.get	0
	i32.const	1
	i32.add 
	local.set	0
	local.get	1
	i32.const	1
	i32.add 
	local.set	1
	local.get	4
	i64.const	-1
	i64.add 
	local.tee	4
	i64.eqz
	i32.eqz
	br_if   	0                               # 0: up to label67
.LBB56_5:
	end_loop
	end_block                               # label66:
	local.get	3
	local.get	2
	i32.wrap_i64
	i32.add 
	i32.const	0
	i32.store8	0
	local.get	3
	local.set	1
.LBB56_6:
	end_block                               # label65:
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_upper,"",@
	.type	qc_to_upper,@function           # -- Begin function qc_to_upper
qc_to_upper:                            # @qc_to_upper
	.functype	qc_to_upper (i32) -> (i32)
	.local  	i32, i64, i32, i64
# %bb.0:
	i32.const	0
	local.set	1
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label68
# %bb.1:
	local.get	0
	call	strlen
	local.tee	2
	i64.const	1
	i64.add 
	call	malloc
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label68
# %bb.2:
	block   	
	local.get	2
	i64.eqz
	br_if   	0                               # 0: down to label69
# %bb.3:
	local.get	3
	local.set	1
	local.get	2
	local.set	4
.LBB57_4:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label70:
	local.get	1
	local.get	0
	i32.load8_u	0
	call	toupper
	i32.store8	0
	local.get	0
	i32.const	1
	i32.add 
	local.set	0
	local.get	1
	i32.const	1
	i32.add 
	local.set	1
	local.get	4
	i64.const	-1
	i64.add 
	local.tee	4
	i64.eqz
	i32.eqz
	br_if   	0                               # 0: up to label70
.LBB57_5:
	end_loop
	end_block                               # label69:
	local.get	3
	local.get	2
	i32.wrap_i64
	i32.add 
	i32.const	0
	i32.store8	0
	local.get	3
	local.set	1
.LBB57_6:
	end_block                               # label68:
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_substring,"",@
	.type	qc_substring,@function          # -- Begin function qc_substring
qc_substring:                           # @qc_substring
	.functype	qc_substring (i32, i32, i32) -> (i32)
	.local  	i64, i32
# %bb.0:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label71
# %bb.1:
	i32.const	0
	return
.LBB58_2:
	end_block                               # label71:
	local.get	0
	call	strlen
	local.set	3
	block   	
	block   	
	local.get	1
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label73
# %bb.3:
	local.get	2
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label73
# %bb.4:
	local.get	3
	i32.wrap_i64
	local.tee	4
	local.get	1
	i32.gt_s
	br_if   	1                               # 1: down to label72
.LBB58_5:
	end_block                               # label73:
	i64.const	1
	call	malloc
	local.tee	0
	i32.const	0
	i32.store8	0
	local.get	0
	return
.LBB58_6:
	end_block                               # label72:
	block   	
	local.get	4
	local.get	1
	i32.sub 
	local.get	2
	local.get	2
	local.get	1
	i32.add 
	local.get	4
	i32.gt_u
	i32.select
	local.tee	2
	i32.const	1
	i32.add 
	i64.extend_i32_u
	call	malloc
	local.tee	4
	br_if   	0                               # 0: down to label74
# %bb.7:
	i32.const	0
	return
.LBB58_8:
	end_block                               # label74:
	block   	
	local.get	2
	i32.eqz
	br_if   	0                               # 0: down to label75
# %bb.9:
	local.get	4
	local.get	0
	local.get	1
	i32.add 
	local.get	2
	memory.copy	0, 0
.LBB58_10:
	end_block                               # label75:
	local.get	4
	local.get	2
	i32.add 
	i32.const	0
	i32.store8	0
	local.get	4
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_contains,"",@
	.type	qc_contains,@function           # -- Begin function qc_contains
qc_contains:                            # @qc_contains
	.functype	qc_contains (i32, i32) -> (i32)
	.local  	i32
# %bb.0:
	i32.const	0
	local.set	2
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label76
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label76
# %bb.2:
	local.get	0
	local.get	1
	call	strstr
	i32.const	0
	i32.ne  
	local.set	2
.LBB59_3:
	end_block                               # label76:
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_startswith,"",@
	.type	qc_startswith,@function         # -- Begin function qc_startswith
qc_startswith:                          # @qc_startswith
	.functype	qc_startswith (i32, i32) -> (i32)
	.local  	i32
# %bb.0:
	i32.const	0
	local.set	2
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label77
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label77
# %bb.2:
	local.get	0
	local.get	1
	local.get	1
	call	strlen
	call	strncmp
	i32.eqz
	local.set	2
.LBB60_3:
	end_block                               # label77:
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_endswith,"",@
	.type	qc_endswith,@function           # -- Begin function qc_endswith
qc_endswith:                            # @qc_endswith
	.functype	qc_endswith (i32, i32) -> (i32)
	.local  	i32, i64, i64
# %bb.0:
	i32.const	0
	local.set	2
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label78
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label78
# %bb.2:
	local.get	0
	call	strlen
	local.set	3
	local.get	1
	call	strlen
	local.tee	4
	local.get	3
	i64.gt_u
	br_if   	0                               # 0: down to label78
# %bb.3:
	local.get	0
	local.get	3
	i32.wrap_i64
	i32.add 
	local.get	4
	i32.wrap_i64
	i32.sub 
	local.get	1
	call	strcmp
	i32.eqz
	local.set	2
.LBB61_4:
	end_block                               # label78:
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_float,"",@
	.type	qc_print_float,@function        # -- Begin function qc_print_float
qc_print_float:                         # @qc_print_float
	.functype	qc_print_float (f32) -> ()
	.local  	i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	local.get	0
	f64.promote_f32
	f64.store	0
	i32.const	.L.str.35
	local.get	1
	call	printf
	drop
	local.get	1
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_bool_from_string,"",@
	.type	qc_to_bool_from_string,@function # -- Begin function qc_to_bool_from_string
qc_to_bool_from_string:                 # @qc_to_bool_from_string
	.functype	qc_to_bool_from_string (i32) -> (i32)
	.local  	i32
# %bb.0:
	i32.const	0
	local.set	1
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label79
# %bb.1:
	block   	
	local.get	0
	i32.const	.L.str.24
	call	strcmp
	br_if   	0                               # 0: down to label80
# %bb.2:
	i32.const	1
	return
.LBB63_3:
	end_block                               # label80:
	local.get	0
	i32.load8_u	0
	i32.const	49
	i32.ne  
	br_if   	0                               # 0: down to label79
# %bb.4:
	local.get	0
	i32.load8_u	1
	i32.eqz
	local.set	1
.LBB63_5:
	end_block                               # label79:
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_qbool_from_string,"",@
	.type	qc_to_qbool_from_string,@function # -- Begin function qc_to_qbool_from_string
qc_to_qbool_from_string:                # @qc_to_qbool_from_string
	.functype	qc_to_qbool_from_string (i32) -> (i32)
# %bb.0:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label81
# %bb.1:
	i32.const	0
	return
.LBB64_2:
	end_block                               # label81:
	block   	
	local.get	0
	i32.const	.L.str.28
	call	strcmp
	br_if   	0                               # 0: down to label82
# %bb.3:
	i32.const	2
	return
.LBB64_4:
	end_block                               # label82:
	block   	
	local.get	0
	i32.const	.L.str.27
	call	strcmp
	br_if   	0                               # 0: down to label83
# %bb.5:
	i32.const	1
	return
.LBB64_6:
	end_block                               # label83:
	i32.const	0
	i32.const	3
	local.get	0
	i32.const	.L.str.29
	call	strcmp
	i32.select
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_qin,"",@
	.type	qc_qin,@function                # -- Begin function qc_qin
qc_qin:                                 # @qc_qin
	.functype	qc_qin () -> (i32)
	.local  	i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	1040
	i32.sub 
	local.tee	0
	global.set	__stack_pointer
	i32.const	0
	i32.load	stdout
	call	fflush
	drop
	i32.const	0
	i32.load	stderr
	call	fflush
	drop
	i32.const	0
	i32.load	stdin
	call	fflush
	drop
	local.get	0
	local.get	0
	i32.const	16
	i32.add 
	i32.store	0
	i32.const	.L.str.39
	local.get	0
	call	__isoc23_scanf
	local.set	1
	i32.const	0
	i32.load	stderr
	call	fflush
	drop
	i32.const	0
	i32.load	stdin
	call	fflush
	drop
	local.get	0
	i32.const	16
	i32.add 
	i32.const	.L.str.2
	local.get	1
	i32.const	1
	i32.eq  
	i32.select
	call	strdup
	local.set	1
	local.get	0
	i32.const	1040
	i32.add 
	global.set	__stack_pointer
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_bool,"",@
	.type	qc_print_bool,@function         # -- Begin function qc_print_bool
qc_print_bool:                          # @qc_print_bool
	.functype	qc_print_bool (i32) -> ()
	.local  	i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.select
	i32.store	0
	i32.const	.L.str.39
	local.get	1
	call	printf
	drop
	local.get	1
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_trim,"",@
	.type	qc_trim,@function               # -- Begin function qc_trim
qc_trim:                                # @qc_trim
	.functype	qc_trim (i32) -> (i32)
	.local  	i32, i32, i32, i64, i32, i32
# %bb.0:
	i32.const	0
	local.set	1
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label84
# %bb.1:
	block   	
	block   	
	local.get	0
	i32.load8_u	0
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label86
# %bb.2:                                # %.preheader
	local.get	0
	i32.const	-1
	i32.add 
	local.set	3
	local.get	0
	i64.extend_i32_u
	local.set	4
.LBB67_3:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label87:
	local.get	2
	i32.const	255
	i32.and 
	call	isspace
	i32.eqz
	br_if   	2                               # 2: down to label85
# %bb.4:                                #   in Loop: Header=BB67_3 Depth=1
	local.get	4
	i64.const	1
	i64.add 
	local.set	4
	local.get	3
	i32.const	1
	i32.add 
	local.set	3
	local.get	0
	i32.const	1
	i32.add 
	local.tee	0
	i32.load8_u	0
	local.tee	2
	br_if   	0                               # 0: up to label87
.LBB67_5:
	end_loop
	end_block                               # label86:
	i64.const	1
	call	malloc
	local.tee	0
	i32.const	0
	i32.store8	0
	local.get	0
	return
.LBB67_6:
	end_block                               # label85:
	local.get	0
	call	strlen
	i32.wrap_i64
	local.tee	2
	local.get	3
	i32.add 
	local.set	3
	local.get	0
	local.get	2
	i32.add 
	i32.const	-1
	i32.add 
	local.set	2
.LBB67_7:                               # =>This Inner Loop Header: Depth=1
	block   	
	loop    	                                # label89:
	local.get	3
	local.set	5
	local.get	2
	local.get	0
	i32.le_u
	br_if   	1                               # 1: down to label88
# %bb.8:                                #   in Loop: Header=BB67_7 Depth=1
	local.get	5
	i32.const	-1
	i32.add 
	local.set	3
	local.get	2
	i32.load8_u	0
	local.set	6
	local.get	2
	i32.const	-1
	i32.add 
	local.set	2
	local.get	6
	call	isspace
	br_if   	0                               # 0: up to label89
.LBB67_9:
	end_loop
	end_block                               # label88:
	local.get	5
	i64.extend_i32_u
	local.get	4
	i64.sub 
	local.tee	4
	i64.const	2
	i64.add 
	call	malloc
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label84
# %bb.10:
	block   	
	local.get	4
	i32.wrap_i64
	i32.const	1
	i32.add 
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label90
# %bb.11:
	local.get	2
	local.get	0
	local.get	3
	memory.copy	0, 0
.LBB67_12:
	end_block                               # label90:
	local.get	2
	local.get	3
	i32.add 
	i32.const	0
	i32.store8	0
	local.get	2
	local.set	1
.LBB67_13:
	end_block                               # label84:
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_replace,"",@
	.type	qc_replace,@function            # -- Begin function qc_replace
qc_replace:                             # @qc_replace
	.functype	qc_replace (i32, i32, i32) -> (i32)
	.local  	i32, i64, i64, i32, i64, i64, i32, i32
# %bb.0:
	i32.const	0
	local.set	3
	block   	
	block   	
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label93
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label93
# %bb.2:
	local.get	2
	i32.eqz
	br_if   	0                               # 0: down to label93
# %bb.3:
	local.get	1
	call	strlen
	local.set	4
	local.get	2
	call	strlen
	local.set	5
	local.get	4
	i64.eqz
	br_if   	1                               # 1: down to label92
# %bb.4:
	local.get	0
	local.get	1
	call	strstr
	local.tee	6
	i32.eqz
	br_if   	2                               # 2: down to label91
# %bb.5:                                # %.preheader1
	local.get	5
	local.get	4
	i64.sub 
	local.set	7
	i64.const	1
	local.set	8
	local.get	4
	i32.wrap_i64
	local.set	9
.LBB68_6:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label94:
	local.get	8
	local.get	7
	i64.add 
	local.set	8
	local.get	6
	local.get	9
	i32.add 
	local.get	1
	call	strstr
	local.tee	6
	br_if   	0                               # 0: up to label94
# %bb.7:
	end_loop
	local.get	0
	call	strlen
	local.get	8
	i64.add 
	call	malloc
	local.tee	10
	i32.eqz
	br_if   	0                               # 0: down to label93
# %bb.8:
	local.get	10
	local.set	6
	block   	
	local.get	0
	i32.load8_u	0
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label95
# %bb.9:                                # %.preheader
	local.get	10
	local.set	6
.LBB68_10:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label96:
	block   	
	block   	
	local.get	0
	local.get	1
	local.get	1
	call	strlen
	call	strncmp
	br_if   	0                               # 0: down to label98
# %bb.11:                               #   in Loop: Header=BB68_10 Depth=1
	block   	
	local.get	5
	i32.wrap_i64
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label99
# %bb.12:                               #   in Loop: Header=BB68_10 Depth=1
	local.get	6
	local.get	2
	local.get	3
	memory.copy	0, 0
.LBB68_13:                              #   in Loop: Header=BB68_10 Depth=1
	end_block                               # label99:
	local.get	0
	local.get	9
	i32.add 
	local.set	0
	local.get	6
	local.get	3
	i32.add 
	local.set	6
	br      	1                               # 1: down to label97
.LBB68_14:                              #   in Loop: Header=BB68_10 Depth=1
	end_block                               # label98:
	local.get	6
	local.get	3
	i32.store8	0
	local.get	6
	i32.const	1
	i32.add 
	local.set	6
	local.get	0
	i32.const	1
	i32.add 
	local.set	0
.LBB68_15:                              #   in Loop: Header=BB68_10 Depth=1
	end_block                               # label97:
	local.get	0
	i32.load8_u	0
	local.tee	3
	br_if   	0                               # 0: up to label96
.LBB68_16:
	end_loop
	end_block                               # label95:
	local.get	6
	i32.const	0
	i32.store8	0
	local.get	10
	local.set	3
.LBB68_17:
	end_block                               # label93:
	local.get	3
	return
.LBB68_18:
	end_block                               # label92:
	local.get	0
	call	strlen
	i64.const	1
	i64.add 
	call	malloc
	local.get	0
	call	strcpy
	return
.LBB68_19:
	end_block                               # label91:
	local.get	0
	call	strlen
	i64.const	1
	i64.add 
	call	malloc
	local.get	0
	call	strcpy
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_int_from_string,"",@
	.type	qc_to_int_from_string,@function # -- Begin function qc_to_int_from_string
qc_to_int_from_string:                  # @qc_to_int_from_string
	.functype	qc_to_int_from_string (i32) -> (i32)
# %bb.0:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label100
# %bb.1:
	i32.const	0
	return
.LBB69_2:
	end_block                               # label100:
	local.get	0
	i32.const	0
	i32.const	10
	call	__isoc23_strtol
	i32.wrap_i64
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_short_int_from_string,"",@
	.type	qc_to_short_int_from_string,@function # -- Begin function qc_to_short_int_from_string
qc_to_short_int_from_string:            # @qc_to_short_int_from_string
	.functype	qc_to_short_int_from_string (i32) -> (i32)
# %bb.0:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label101
# %bb.1:
	i32.const	0
	i32.extend16_s
	return
.LBB70_2:
	end_block                               # label101:
	local.get	0
	i32.const	0
	i32.const	10
	call	__isoc23_strtol
	i32.wrap_i64
	i32.extend16_s
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_long_int_from_string,"",@
	.type	qc_to_long_int_from_string,@function # -- Begin function qc_to_long_int_from_string
qc_to_long_int_from_string:             # @qc_to_long_int_from_string
	.functype	qc_to_long_int_from_string (i32) -> (i64)
# %bb.0:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label102
# %bb.1:
	i64.const	0
	return
.LBB71_2:
	end_block                               # label102:
	local.get	0
	i32.const	0
	i32.const	10
	call	__isoc23_strtoll
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_addr_t_from_string,"",@
	.type	qc_to_addr_t_from_string,@function # -- Begin function qc_to_addr_t_from_string
qc_to_addr_t_from_string:               # @qc_to_addr_t_from_string
	.functype	qc_to_addr_t_from_string (i32) -> (i64)
# %bb.0:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label103
# %bb.1:
	i64.const	0
	return
.LBB72_2:
	end_block                               # label103:
	local.get	0
	i32.const	0
	i32.const	10
	call	__isoc23_strtoull
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_float_from_string,"",@
	.type	qc_to_float_from_string,@function # -- Begin function qc_to_float_from_string
qc_to_float_from_string:                # @qc_to_float_from_string
	.functype	qc_to_float_from_string (i32) -> (f32)
# %bb.0:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label104
# %bb.1:
	f32.const	0x0p0
	return
.LBB73_2:
	end_block                               # label104:
	local.get	0
	i32.const	0
	call	strtod
	f32.demote_f64
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_double_from_string,"",@
	.type	qc_to_double_from_string,@function # -- Begin function qc_to_double_from_string
qc_to_double_from_string:               # @qc_to_double_from_string
	.functype	qc_to_double_from_string (i32) -> (f64)
# %bb.0:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label105
# %bb.1:
	f64.const	0x0p0
	return
.LBB74_2:
	end_block                               # label105:
	local.get	0
	i32.const	0
	call	strtod
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_char_from_string,"",@
	.type	qc_to_char_from_string,@function # -- Begin function qc_to_char_from_string
qc_to_char_from_string:                 # @qc_to_char_from_string
	.functype	qc_to_char_from_string (i32) -> (i32)
# %bb.0:
	block   	
	local.get	0
	br_if   	0                               # 0: down to label106
# %bb.1:
	i32.const	0
	i32.extend8_s
	return
.LBB75_2:
	end_block                               # label106:
	local.get	0
	i32.load8_u	0
	i32.extend8_s
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_int_from_bool,"",@
	.type	qc_to_int_from_bool,@function   # -- Begin function qc_to_int_from_bool
qc_to_int_from_bool:                    # @qc_to_int_from_bool
	.functype	qc_to_int_from_bool (i32) -> (i32)
# %bb.0:
	local.get	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_float_from_int,"",@
	.type	qc_to_float_from_int,@function  # -- Begin function qc_to_float_from_int
qc_to_float_from_int:                   # @qc_to_float_from_int
	.functype	qc_to_float_from_int (i32) -> (f32)
# %bb.0:
	local.get	0
	f32.convert_i32_s
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_to_double_from_int,"",@
	.type	qc_to_double_from_int,@function # -- Begin function qc_to_double_from_int
qc_to_double_from_int:                  # @qc_to_double_from_int
	.functype	qc_to_double_from_int (i32) -> (f64)
# %bb.0:
	local.get	0
	f64.convert_i32_s
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print,"",@
	.type	qc_print,@function              # -- Begin function qc_print
qc_print:                               # @qc_print
	.functype	qc_print (i32) -> ()
	.local  	i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label107
# %bb.1:
	local.get	1
	local.get	0
	i32.store	0
	i32.const	.L.str.39
	local.get	1
	call	printf
	drop
.LBB79_2:
	end_block                               # label107:
	local.get	1
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_println,"",@
	.type	qc_println,@function            # -- Begin function qc_println
qc_println:                             # @qc_println
	.functype	qc_println (i32) -> ()
# %bb.0:
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label108
# %bb.1:
	local.get	0
	call	puts
	drop
	return
.LBB80_2:
	end_block                               # label108:
	i32.const	10
	i32.const	0
	i32.load	stdout
	call	putc
	drop
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_array_int,"",@
	.type	qc_print_array_int,@function    # -- Begin function qc_print_array_int
qc_print_array_int:                     # @qc_print_array_int
	.functype	qc_print_array_int (i32, i32) -> ()
	.local  	i32, i64, i64, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	2
	global.set	__stack_pointer
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label109
# %bb.1:
	local.get	1
	i32.const	-1
	i32.add 
	i64.extend_i32_u
	local.set	3
	local.get	1
	i64.extend_i32_u
	local.set	4
	i64.const	0
	local.set	5
.LBB81_2:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label110:
	local.get	2
	local.get	0
	i32.load	0
	i32.store	0
	i32.const	.L.str.34
	local.get	2
	call	printf
	drop
	block   	
	local.get	5
	local.get	3
	i64.ge_u
	br_if   	0                               # 0: down to label111
# %bb.3:                                #   in Loop: Header=BB81_2 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
.LBB81_4:                               #   in Loop: Header=BB81_2 Depth=1
	end_block                               # label111:
	local.get	0
	i32.const	4
	i32.add 
	local.set	0
	local.get	4
	local.get	5
	i64.const	1
	i64.add 
	local.tee	5
	i64.ne  
	br_if   	0                               # 0: up to label110
.LBB81_5:
	end_loop
	end_block                               # label109:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	local.get	2
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_array_float,"",@
	.type	qc_print_array_float,@function  # -- Begin function qc_print_array_float
qc_print_array_float:                   # @qc_print_array_float
	.functype	qc_print_array_float (i32, i32) -> ()
	.local  	i32, i64, i64, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	2
	global.set	__stack_pointer
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label112
# %bb.1:
	local.get	1
	i32.const	-1
	i32.add 
	i64.extend_i32_u
	local.set	3
	local.get	1
	i64.extend_i32_u
	local.set	4
	i64.const	0
	local.set	5
.LBB82_2:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label113:
	local.get	2
	local.get	0
	f32.load	0
	f64.promote_f32
	f64.store	0
	i32.const	.L.str.35
	local.get	2
	call	printf
	drop
	block   	
	local.get	5
	local.get	3
	i64.ge_u
	br_if   	0                               # 0: down to label114
# %bb.3:                                #   in Loop: Header=BB82_2 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
.LBB82_4:                               #   in Loop: Header=BB82_2 Depth=1
	end_block                               # label114:
	local.get	0
	i32.const	4
	i32.add 
	local.set	0
	local.get	4
	local.get	5
	i64.const	1
	i64.add 
	local.tee	5
	i64.ne  
	br_if   	0                               # 0: up to label113
.LBB82_5:
	end_loop
	end_block                               # label112:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	local.get	2
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_array_double,"",@
	.type	qc_print_array_double,@function # -- Begin function qc_print_array_double
qc_print_array_double:                  # @qc_print_array_double
	.functype	qc_print_array_double (i32, i32) -> ()
	.local  	i32, i64, i64, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	2
	global.set	__stack_pointer
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label115
# %bb.1:
	local.get	1
	i32.const	-1
	i32.add 
	i64.extend_i32_u
	local.set	3
	local.get	1
	i64.extend_i32_u
	local.set	4
	i64.const	0
	local.set	5
.LBB83_2:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label116:
	local.get	2
	local.get	0
	f64.load	0
	f64.store	0
	i32.const	.L.str.35
	local.get	2
	call	printf
	drop
	block   	
	local.get	5
	local.get	3
	i64.ge_u
	br_if   	0                               # 0: down to label117
# %bb.3:                                #   in Loop: Header=BB83_2 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
.LBB83_4:                               #   in Loop: Header=BB83_2 Depth=1
	end_block                               # label117:
	local.get	0
	i32.const	8
	i32.add 
	local.set	0
	local.get	4
	local.get	5
	i64.const	1
	i64.add 
	local.tee	5
	i64.ne  
	br_if   	0                               # 0: up to label116
.LBB83_5:
	end_loop
	end_block                               # label115:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	local.get	2
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_array_string,"",@
	.type	qc_print_array_string,@function # -- Begin function qc_print_array_string
qc_print_array_string:                  # @qc_print_array_string
	.functype	qc_print_array_string (i32, i32) -> ()
	.local  	i32, i64, i64, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	2
	global.set	__stack_pointer
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label118
# %bb.1:
	local.get	1
	i32.const	-1
	i32.add 
	i64.extend_i32_u
	local.set	3
	local.get	1
	i64.extend_i32_u
	local.set	4
	i64.const	0
	local.set	5
.LBB84_2:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label119:
	local.get	2
	local.get	0
	i32.load	0
	i32.store	0
	i32.const	.L.str.45
	local.get	2
	call	printf
	drop
	block   	
	local.get	5
	local.get	3
	i64.ge_u
	br_if   	0                               # 0: down to label120
# %bb.3:                                #   in Loop: Header=BB84_2 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
.LBB84_4:                               #   in Loop: Header=BB84_2 Depth=1
	end_block                               # label120:
	local.get	0
	i32.const	4
	i32.add 
	local.set	0
	local.get	4
	local.get	5
	i64.const	1
	i64.add 
	local.tee	5
	i64.ne  
	br_if   	0                               # 0: up to label119
.LBB84_5:
	end_loop
	end_block                               # label118:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	local.get	2
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_array_char,"",@
	.type	qc_print_array_char,@function   # -- Begin function qc_print_array_char
qc_print_array_char:                    # @qc_print_array_char
	.functype	qc_print_array_char (i32, i32) -> ()
	.local  	i32, i64, i64, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	2
	global.set	__stack_pointer
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label121
# %bb.1:
	local.get	1
	i32.const	-1
	i32.add 
	i64.extend_i32_u
	local.set	3
	local.get	1
	i64.extend_i32_u
	local.set	4
	i64.const	0
	local.set	5
.LBB85_2:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label122:
	local.get	2
	local.get	0
	i32.load8_s	0
	i32.store	0
	i32.const	.L.str.46
	local.get	2
	call	printf
	drop
	block   	
	local.get	5
	local.get	3
	i64.ge_u
	br_if   	0                               # 0: down to label123
# %bb.3:                                #   in Loop: Header=BB85_2 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
.LBB85_4:                               #   in Loop: Header=BB85_2 Depth=1
	end_block                               # label123:
	local.get	0
	i32.const	1
	i32.add 
	local.set	0
	local.get	4
	local.get	5
	i64.const	1
	i64.add 
	local.tee	5
	i64.ne  
	br_if   	0                               # 0: up to label122
.LBB85_5:
	end_loop
	end_block                               # label121:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	local.get	2
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_array_bool,"",@
	.type	qc_print_array_bool,@function   # -- Begin function qc_print_array_bool
qc_print_array_bool:                    # @qc_print_array_bool
	.functype	qc_print_array_bool (i32, i32) -> ()
	.local  	i32, i64, i64, i64
# %bb.0:
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	2
	global.set	__stack_pointer
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label124
# %bb.1:
	local.get	1
	i32.const	-1
	i32.add 
	i64.extend_i32_u
	local.set	3
	local.get	1
	i64.extend_i32_u
	local.set	4
	i64.const	0
	local.set	5
.LBB86_2:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label125:
	local.get	2
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.load8_u	0
	i32.select
	i32.store	0
	i32.const	.L.str.39
	local.get	2
	call	printf
	drop
	block   	
	local.get	5
	local.get	3
	i64.ge_u
	br_if   	0                               # 0: down to label126
# %bb.3:                                #   in Loop: Header=BB86_2 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
.LBB86_4:                               #   in Loop: Header=BB86_2 Depth=1
	end_block                               # label126:
	local.get	0
	i32.const	1
	i32.add 
	local.set	0
	local.get	4
	local.get	5
	i64.const	1
	i64.add 
	local.tee	5
	i64.ne  
	br_if   	0                               # 0: up to label125
.LBB86_5:
	end_loop
	end_block                               # label124:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	local.get	2
	i32.const	16
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_array_qbool,"",@
	.type	qc_print_array_qbool,@function  # -- Begin function qc_print_array_qbool
qc_print_array_qbool:                   # @qc_print_array_qbool
	.functype	qc_print_array_qbool (i32, i32) -> ()
	.local  	i64, i64, i64
# %bb.0:
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label127
# %bb.1:
	local.get	1
	i32.const	-1
	i32.add 
	i64.extend_i32_u
	local.set	2
	local.get	1
	i64.extend_i32_u
	local.set	3
	i64.const	0
	local.set	4
.LBB87_2:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label128:
	local.get	0
	i32.load8_u	0
	i32.const	3
	i32.and 
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_print_array_qbool
	i32.const	0
	call	printf
	drop
	block   	
	local.get	4
	local.get	2
	i64.ge_u
	br_if   	0                               # 0: down to label129
# %bb.3:                                #   in Loop: Header=BB87_2 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
.LBB87_4:                               #   in Loop: Header=BB87_2 Depth=1
	end_block                               # label129:
	local.get	0
	i32.const	1
	i32.add 
	local.set	0
	local.get	3
	local.get	4
	i64.const	1
	i64.add 
	local.tee	4
	i64.ne  
	br_if   	0                               # 0: up to label128
.LBB87_5:
	end_loop
	end_block                               # label127:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_sizeof_type,"",@
	.type	qc_sizeof_type,@function        # -- Begin function qc_sizeof_type
qc_sizeof_type:                         # @qc_sizeof_type
	.functype	qc_sizeof_type (i32) -> (i32)
	.local  	i32
# %bb.0:
	i32.const	4
	local.set	1
	block   	
	local.get	0
	i32.const	-2
	i32.add 
	local.tee	0
	i32.const	4
	i32.gt_u
	br_if   	0                               # 0: down to label130
# %bb.1:
	local.get	0
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_stringify_jagged_helper
	local.set	1
.LBB88_2:
	end_block                               # label130:
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_array_to_string_recursive,"",@
	.type	qc_array_to_string_recursive,@function # -- Begin function qc_array_to_string_recursive
qc_array_to_string_recursive:           # @qc_array_to_string_recursive
	.functype	qc_array_to_string_recursive (i32, i32, i32, i32) -> (i32)
	.local  	i32, i32, i32, i32, i64, i64, i64, i64, i32, i64, i32, i32, i32, i32, i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	368
	i32.sub 
	local.tee	4
	global.set	__stack_pointer
	block   	
	block   	
	local.get	2
	br_if   	0                               # 0: down to label132
# %bb.1:
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	1
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label139
                                        # 2: down to label138
                                        # 3: down to label137
                                        # 4: down to label136
                                        # 5: down to label135
                                        # 6: down to label134
                                        # 7: down to label133
.LBB89_2:
	end_block                               # label140:
	local.get	4
	local.get	0
	i32.load	0
	i32.store	0
	local.get	4
	i32.const	112
	i32.add 
	i64.const	256
	i32.const	.L.str.34
	local.get	4
	call	snprintf
	drop
	br      	6                               # 6: down to label133
.LBB89_3:
	end_block                               # label139:
	local.get	4
	local.get	0
	f32.load	0
	f64.promote_f32
	f64.store	16
	local.get	4
	i32.const	112
	i32.add 
	i64.const	256
	i32.const	.L.str.35
	local.get	4
	i32.const	16
	i32.add 
	call	snprintf
	drop
	br      	5                               # 5: down to label133
.LBB89_4:
	end_block                               # label138:
	local.get	4
	local.get	0
	f64.load	0
	f64.store	32
	local.get	4
	i32.const	112
	i32.add 
	i64.const	256
	i32.const	.L.str.35
	local.get	4
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	4                               # 4: down to label133
.LBB89_5:
	end_block                               # label137:
	local.get	4
	local.get	0
	i32.load8_s	0
	i32.store	48
	local.get	4
	i32.const	112
	i32.add 
	i64.const	256
	i32.const	.L.str.46
	local.get	4
	i32.const	48
	i32.add 
	call	snprintf
	drop
	br      	3                               # 3: down to label133
.LBB89_6:
	end_block                               # label136:
	local.get	4
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.load8_u	0
	i32.select
	i32.store	64
	local.get	4
	i32.const	112
	i32.add 
	i64.const	256
	i32.const	.L.str.39
	local.get	4
	i32.const	64
	i32.add 
	call	snprintf
	drop
	br      	2                               # 2: down to label133
.LBB89_7:
	end_block                               # label135:
	i32.const	.L.str.26
	local.set	5
	block   	
	block   	
	block   	
	local.get	0
	i32.load8_u	0
	i32.const	3
	i32.and 
	local.tee	0
	br_table 	{2, 1, 0}               # 1: down to label142
                                        # 0: down to label143
.LBB89_8:
	end_block                               # label143:
	i32.const	.L.str.28
	i32.const	.L.str.29
	local.get	0
	i32.const	2
	i32.eq  
	i32.select
	local.set	5
	br      	1                               # 1: down to label141
.LBB89_9:
	end_block                               # label142:
	i32.const	.L.str.27
	local.set	5
.LBB89_10:
	end_block                               # label141:
	local.get	4
	local.get	5
	i32.store	80
	local.get	4
	i32.const	112
	i32.add 
	i64.const	256
	i32.const	.L.str.39
	local.get	4
	i32.const	80
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label133
.LBB89_11:
	end_block                               # label134:
	local.get	4
	local.get	0
	i32.load	0
	i32.store	96
	local.get	4
	i32.const	112
	i32.add 
	i64.const	256
	i32.const	.L.str.45
	local.get	4
	i32.const	96
	i32.add 
	call	snprintf
	drop
.LBB89_12:
	end_block                               # label133:
	local.get	4
	i32.const	112
	i32.add 
	call	strlen
	i64.const	1
	i64.add 
	call	malloc
	local.get	4
	i32.const	112
	i32.add 
	call	strcpy
	local.set	6
	br      	1                               # 1: down to label131
.LBB89_13:
	end_block                               # label132:
	i32.const	4
	local.set	5
	block   	
	local.get	1
	i32.const	-2
	i32.add 
	local.tee	7
	i32.const	4
	i32.gt_u
	br_if   	0                               # 0: down to label144
# %bb.14:
	local.get	7
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_stringify_jagged_helper
	local.set	5
.LBB89_15:
	end_block                               # label144:
	block   	
	local.get	2
	i32.const	2
	i32.lt_s
	br_if   	0                               # 0: down to label145
# %bb.16:
	local.get	2
	i64.extend_i32_u
	local.set	8
	i64.const	1
	local.set	9
	block   	
	local.get	2
	i32.const	9
	i32.lt_u
	br_if   	0                               # 0: down to label146
# %bb.17:
	local.get	3
	i32.const	20
	i32.add 
	local.set	7
	local.get	8
	i64.const	-1
	i64.add 
	local.tee	10
	i64.const	-8
	i64.and 
	local.tee	11
	i64.const	1
	i64.or  
	local.set	9
	i32.const	1
	local.set	12
	local.get	11
	local.set	13
	i32.const	1
	local.set	14
	i32.const	1
	local.set	15
	i32.const	1
	local.set	16
	i32.const	1
	local.set	17
	i32.const	1
	local.set	18
	i32.const	1
	local.set	19
.LBB89_18:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label147:
	local.get	7
	i32.load	4
	local.get	17
	i32.mul 
	local.set	17
	local.get	7
	i32.load	0
	local.get	16
	i32.mul 
	local.set	16
	local.get	7
	i32.load	8
	local.get	18
	i32.mul 
	local.set	18
	local.get	7
	i32.const	-16
	i32.add 
	local.tee	6
	i32.load	8
	local.get	14
	i32.mul 
	local.set	14
	local.get	6
	i32.load	4
	local.get	12
	i32.mul 
	local.set	12
	local.get	6
	i32.load	0
	local.get	5
	i32.mul 
	local.set	5
	local.get	7
	i32.load	12
	local.get	19
	i32.mul 
	local.set	19
	local.get	6
	i32.load	12
	local.get	15
	i32.mul 
	local.set	15
	local.get	7
	i32.const	32
	i32.add 
	local.set	7
	local.get	13
	i64.const	-8
	i64.add 
	local.tee	13
	i64.const	0
	i64.ne  
	br_if   	0                               # 0: up to label147
# %bb.19:
	end_loop
	local.get	16
	local.get	5
	i32.mul 
	local.get	18
	local.get	14
	i32.mul 
	i32.mul 
	local.get	17
	local.get	12
	i32.mul 
	local.get	19
	local.get	15
	i32.mul 
	i32.mul 
	i32.mul 
	local.set	5
	local.get	10
	local.get	11
	i64.eq  
	br_if   	1                               # 1: down to label145
.LBB89_20:
	end_block                               # label146:
	local.get	8
	local.get	9
	i64.sub 
	local.set	13
	local.get	3
	local.get	9
	i32.wrap_i64
	i32.const	2
	i32.shl 
	i32.add 
	local.set	7
.LBB89_21:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label148:
	local.get	7
	i32.load	0
	local.get	5
	i32.mul 
	local.set	5
	local.get	7
	i32.const	4
	i32.add 
	local.set	7
	local.get	13
	i64.const	-1
	i64.add 
	local.tee	13
	i64.eqz
	i32.eqz
	br_if   	0                               # 0: up to label148
.LBB89_22:
	end_loop
	end_block                               # label145:
	i64.const	0
	local.set	13
	local.get	3
	i64.load32_s	0
	local.tee	9
	i64.const	3
	i64.shl 
	call	malloc
	local.set	16
	block   	
	block   	
	local.get	9
	i64.const	0
	i64.gt_s
	br_if   	0                               # 0: down to label150
# %bb.23:
	i64.const	3
	call	malloc
	local.tee	6
	i32.const	91
	i32.store8	0
	local.get	6
	i32.const	1
	i32.add 
	local.set	5
	br      	1                               # 1: down to label149
.LBB89_24:
	end_block                               # label150:
	local.get	3
	i32.const	4
	i32.add 
	local.set	14
	local.get	2
	i32.const	-1
	i32.add 
	local.set	15
	local.get	16
	local.set	7
	i32.const	2
	local.set	6
.LBB89_25:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label151:
	local.get	7
	local.get	0
	local.get	1
	local.get	15
	local.get	14
	call	qc_array_to_string_recursive
	local.tee	12
	i32.store	0
	local.get	6
	local.get	12
	call	strlen
	i32.wrap_i64
	i32.add 
	local.tee	6
	i32.const	2
	i32.add 
	local.get	6
	local.get	13
	local.get	3
	i32.load	0
	local.tee	12
	i32.const	-1
	i32.add 
	i64.extend_i32_s
	i64.lt_s
	i32.select
	local.set	6
	local.get	0
	local.get	5
	i32.add 
	local.set	0
	local.get	7
	i32.const	4
	i32.add 
	local.set	7
	local.get	13
	i64.const	1
	i64.add 
	local.tee	13
	local.get	12
	i64.extend_i32_s
	i64.lt_s
	br_if   	0                               # 0: up to label151
# %bb.26:
	end_loop
	local.get	6
	i32.const	1
	i32.add 
	i64.extend_i32_s
	call	malloc
	local.tee	6
	i32.const	91
	i32.store8	0
	local.get	6
	i32.const	1
	i32.add 
	local.set	5
	local.get	12
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label149
# %bb.27:                               # %.preheader
	i64.const	0
	local.set	13
	local.get	16
	local.set	0
.LBB89_28:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label152:
	local.get	5
	local.get	0
	i32.load	0
	call	strcpy
	local.set	5
	local.get	0
	i32.load	0
	local.tee	7
	call	strlen
	local.set	9
	local.get	7
	call	free
	local.get	5
	local.get	9
	i32.wrap_i64
	i32.add 
	local.set	5
	block   	
	local.get	13
	local.get	3
	i32.load	0
	local.tee	7
	i32.const	-1
	i32.add 
	i64.extend_i32_s
	i64.ge_s
	br_if   	0                               # 0: down to label153
# %bb.29:                               #   in Loop: Header=BB89_28 Depth=1
	local.get	5
	i32.const	8236
	i32.store16	0:p2align=0
	local.get	5
	i32.const	2
	i32.add 
	local.set	5
	local.get	3
	i32.load	0
	local.set	7
.LBB89_30:                              #   in Loop: Header=BB89_28 Depth=1
	end_block                               # label153:
	local.get	0
	i32.const	4
	i32.add 
	local.set	0
	local.get	13
	i64.const	1
	i64.add 
	local.tee	13
	local.get	7
	i64.extend_i32_s
	i64.lt_s
	br_if   	0                               # 0: up to label152
.LBB89_31:
	end_loop
	end_block                               # label149:
	local.get	5
	i32.const	93
	i32.store16	0:p2align=0
	local.get	16
	call	free
.LBB89_32:
	end_block                               # label131:
	local.get	4
	i32.const	368
	i32.add 
	global.set	__stack_pointer
	local.get	6
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_array_recursive,"",@
	.type	qc_print_array_recursive,@function # -- Begin function qc_print_array_recursive
qc_print_array_recursive:               # @qc_print_array_recursive
	.functype	qc_print_array_recursive (i32, i32, i32, i32) -> ()
	.local  	i32, i32, i32, i64, i64, i64, i64, i32, i64, i32, i32, i32, i32, i32, i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	96
	i32.sub 
	local.tee	4
	global.set	__stack_pointer
	block   	
	block   	
	block   	
	local.get	2
	br_if   	0                               # 0: down to label156
# %bb.1:
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	1
	br_table 	{7, 0, 1, 2, 3, 4, 5, 8} # 0: down to label162
                                        # 1: down to label161
                                        # 2: down to label160
                                        # 3: down to label159
                                        # 4: down to label158
                                        # 5: down to label157
                                        # 8: down to label154
.LBB90_2:
	end_block                               # label162:
	local.get	4
	local.get	0
	f32.load	0
	f64.promote_f32
	f64.store	16
	i32.const	.L.str.35
	local.get	4
	i32.const	16
	i32.add 
	call	printf
	drop
	br      	7                               # 7: down to label154
.LBB90_3:
	end_block                               # label161:
	local.get	4
	local.get	0
	f64.load	0
	f64.store	32
	i32.const	.L.str.35
	local.get	4
	i32.const	32
	i32.add 
	call	printf
	drop
	br      	6                               # 6: down to label154
.LBB90_4:
	end_block                               # label160:
	local.get	4
	local.get	0
	i32.load8_s	0
	i32.store	48
	i32.const	.L.str.46
	local.get	4
	i32.const	48
	i32.add 
	call	printf
	drop
	br      	5                               # 5: down to label154
.LBB90_5:
	end_block                               # label159:
	local.get	4
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.load8_u	0
	i32.select
	i32.store	64
	i32.const	.L.str.39
	local.get	4
	i32.const	64
	i32.add 
	call	printf
	drop
	br      	4                               # 4: down to label154
.LBB90_6:
	end_block                               # label158:
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load8_u	0
	i32.const	3
	i32.and 
	br_table 	{0, 1, 2, 3, 0}         # 1: down to label165
                                        # 2: down to label164
                                        # 3: down to label163
                                        # 0: down to label166
.LBB90_7:
	end_block                               # label166:
	i32.const	.L.str.26
	i32.const	0
	call	printf
	drop
	br      	6                               # 6: down to label154
.LBB90_8:
	end_block                               # label165:
	i32.const	.L.str.27
	i32.const	0
	call	printf
	drop
	br      	5                               # 5: down to label154
.LBB90_9:
	end_block                               # label164:
	i32.const	.L.str.28
	i32.const	0
	call	printf
	drop
	br      	4                               # 4: down to label154
.LBB90_10:
	end_block                               # label163:
	i32.const	.L.str.29
	i32.const	0
	call	printf
	drop
	br      	3                               # 3: down to label154
.LBB90_11:
	end_block                               # label157:
	local.get	4
	local.get	0
	i32.load	0
	i32.store	80
	i32.const	.L.str.45
	local.get	4
	i32.const	80
	i32.add 
	call	printf
	drop
	br      	2                               # 2: down to label154
.LBB90_12:
	end_block                               # label156:
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	i32.const	4
	local.set	5
	block   	
	local.get	1
	i32.const	-2
	i32.add 
	local.tee	6
	i32.const	4
	i32.gt_u
	br_if   	0                               # 0: down to label167
# %bb.13:
	local.get	6
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_stringify_jagged_helper
	local.set	5
.LBB90_14:
	end_block                               # label167:
	block   	
	local.get	2
	i32.const	2
	i32.lt_s
	br_if   	0                               # 0: down to label168
# %bb.15:
	local.get	2
	i64.extend_i32_u
	local.set	7
	i64.const	1
	local.set	8
	block   	
	local.get	2
	i32.const	9
	i32.lt_u
	br_if   	0                               # 0: down to label169
# %bb.16:
	local.get	3
	i32.const	20
	i32.add 
	local.set	6
	local.get	7
	i64.const	-1
	i64.add 
	local.tee	9
	i64.const	-8
	i64.and 
	local.tee	10
	i64.const	1
	i64.or  
	local.set	8
	i32.const	1
	local.set	11
	local.get	10
	local.set	12
	i32.const	1
	local.set	13
	i32.const	1
	local.set	14
	i32.const	1
	local.set	15
	i32.const	1
	local.set	16
	i32.const	1
	local.set	17
	i32.const	1
	local.set	18
.LBB90_17:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label170:
	local.get	6
	i32.load	4
	local.get	16
	i32.mul 
	local.set	16
	local.get	6
	i32.load	0
	local.get	15
	i32.mul 
	local.set	15
	local.get	6
	i32.load	8
	local.get	17
	i32.mul 
	local.set	17
	local.get	6
	i32.const	-16
	i32.add 
	local.tee	19
	i32.load	8
	local.get	13
	i32.mul 
	local.set	13
	local.get	19
	i32.load	4
	local.get	11
	i32.mul 
	local.set	11
	local.get	19
	i32.load	0
	local.get	5
	i32.mul 
	local.set	5
	local.get	6
	i32.load	12
	local.get	18
	i32.mul 
	local.set	18
	local.get	19
	i32.load	12
	local.get	14
	i32.mul 
	local.set	14
	local.get	6
	i32.const	32
	i32.add 
	local.set	6
	local.get	12
	i64.const	-8
	i64.add 
	local.tee	12
	i64.const	0
	i64.ne  
	br_if   	0                               # 0: up to label170
# %bb.18:
	end_loop
	local.get	15
	local.get	5
	i32.mul 
	local.get	17
	local.get	13
	i32.mul 
	i32.mul 
	local.get	16
	local.get	11
	i32.mul 
	local.get	18
	local.get	14
	i32.mul 
	i32.mul 
	i32.mul 
	local.set	5
	local.get	9
	local.get	10
	i64.eq  
	br_if   	1                               # 1: down to label168
.LBB90_19:
	end_block                               # label169:
	local.get	7
	local.get	8
	i64.sub 
	local.set	12
	local.get	3
	local.get	8
	i32.wrap_i64
	i32.const	2
	i32.shl 
	i32.add 
	local.set	6
.LBB90_20:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label171:
	local.get	6
	i32.load	0
	local.get	5
	i32.mul 
	local.set	5
	local.get	6
	i32.const	4
	i32.add 
	local.set	6
	local.get	12
	i64.const	-1
	i64.add 
	local.tee	12
	i64.eqz
	i32.eqz
	br_if   	0                               # 0: up to label171
.LBB90_21:
	end_loop
	end_block                               # label168:
	block   	
	local.get	3
	i32.load	0
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label172
# %bb.22:
	local.get	3
	i32.const	4
	i32.add 
	local.set	19
	local.get	2
	i32.const	-1
	i32.add 
	local.set	11
	i64.const	0
	local.set	12
.LBB90_23:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label173:
	local.get	0
	local.get	1
	local.get	11
	local.get	19
	call	qc_print_array_recursive
	block   	
	local.get	12
	local.get	3
	i32.load	0
	local.tee	6
	i32.const	-1
	i32.add 
	i64.extend_i32_s
	i64.ge_s
	br_if   	0                               # 0: down to label174
# %bb.24:                               #   in Loop: Header=BB90_23 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
	local.get	3
	i32.load	0
	local.set	6
.LBB90_25:                              #   in Loop: Header=BB90_23 Depth=1
	end_block                               # label174:
	local.get	0
	local.get	5
	i32.add 
	local.set	0
	local.get	12
	i64.const	1
	i64.add 
	local.tee	12
	local.get	6
	i64.extend_i32_s
	i64.lt_s
	br_if   	0                               # 0: up to label173
.LBB90_26:
	end_loop
	end_block                               # label172:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	br      	1                               # 1: down to label154
.LBB90_27:
	end_block                               # label155:
	local.get	4
	local.get	0
	i32.load	0
	i32.store	0
	i32.const	.L.str.34
	local.get	4
	call	printf
	drop
.LBB90_28:
	end_block                               # label154:
	local.get	4
	i32.const	96
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_create_jagged_array,"",@
	.type	qc_create_jagged_array,@function # -- Begin function qc_create_jagged_array
qc_create_jagged_array:                 # @qc_create_jagged_array
	.functype	qc_create_jagged_array (i32, i32, i32) -> (i32)
	.local  	i32, i64, i32
# %bb.0:
	i64.const	32
	call	malloc
	local.tee	3
	local.get	0
	i64.extend_i32_s
	local.tee	4
	i64.const	3
	i64.shl 
	call	malloc
	i32.store	0
	local.get	4
	i64.const	2
	i64.shl 
	call	malloc
	local.set	5
	local.get	3
	local.get	2
	i32.store	24
	local.get	3
	local.get	1
	i32.store	20
	local.get	3
	local.get	0
	i32.store	16
	local.get	3
	local.get	5
	i32.store	8
	local.get	3
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_set_jagged_element,"",@
	.type	qc_set_jagged_element,@function # -- Begin function qc_set_jagged_element
qc_set_jagged_element:                  # @qc_set_jagged_element
	.functype	qc_set_jagged_element (i32, i32, i32, i32) -> ()
# %bb.0:
	local.get	0
	i32.load	0
	local.get	1
	i32.const	2
	i32.shl 
	local.tee	1
	i32.add 
	local.get	2
	i32.store	0
	local.get	0
	i32.load	8
	local.get	1
	i32.add 
	local.get	3
	i32.store	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_free_jagged_array,"",@
	.type	qc_free_jagged_array,@function  # -- Begin function qc_free_jagged_array
qc_free_jagged_array:                   # @qc_free_jagged_array
	.functype	qc_free_jagged_array (i32) -> ()
	.local  	i32, i64
# %bb.0:
	local.get	0
	i32.load	16
	local.set	1
	block   	
	block   	
	local.get	0
	i32.load	24
	i32.const	0
	i32.gt_s
	br_if   	0                               # 0: down to label176
# %bb.1:
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	1                               # 1: down to label175
# %bb.2:                                # %.preheader1
	i64.const	0
	local.set	2
	i32.const	0
	local.set	1
.LBB93_3:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label177:
	local.get	0
	i32.load	0
	local.get	1
	i32.add 
	i32.load	0
	call	free
	local.get	1
	i32.const	4
	i32.add 
	local.set	1
	local.get	2
	i64.const	1
	i64.add 
	local.tee	2
	local.get	0
	i64.load32_s	16
	i64.lt_s
	br_if   	0                               # 0: up to label177
	br      	2                               # 2: down to label175
.LBB93_4:
	end_loop
	end_block                               # label176:
	local.get	1
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label175
# %bb.5:                                # %.preheader
	i64.const	0
	local.set	2
	i32.const	0
	local.set	1
.LBB93_6:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label178:
	local.get	0
	i32.load	0
	local.get	1
	i32.add 
	i32.load	0
	call	qc_free_jagged_array
	local.get	1
	i32.const	4
	i32.add 
	local.set	1
	local.get	2
	i64.const	1
	i64.add 
	local.tee	2
	local.get	0
	i64.load32_s	16
	i64.lt_s
	br_if   	0                               # 0: up to label178
.LBB93_7:
	end_loop
	end_block                               # label175:
	local.get	0
	i32.load	0
	call	free
	local.get	0
	i32.load	8
	call	free
	local.get	0
	call	free
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_jagged_array_recursive,"",@
	.type	qc_print_jagged_array_recursive,@function # -- Begin function qc_print_jagged_array_recursive
qc_print_jagged_array_recursive:        # @qc_print_jagged_array_recursive
	.functype	qc_print_jagged_array_recursive (i32) -> ()
	.local  	i32, i64, i32, i32, i32, i32, i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	112
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	0
	i32.load	16
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label179
# %bb.1:
	i64.const	0
	local.set	2
.LBB94_2:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB94_7 Depth 2
	loop    	                                # label180:
	block   	
	block   	
	local.get	0
	i32.load	24
	local.tee	3
	i32.const	2
	i32.lt_s
	br_if   	0                               # 0: down to label182
# %bb.3:                                #   in Loop: Header=BB94_2 Depth=1
	local.get	0
	i32.load	0
	local.get	2
	i32.wrap_i64
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	call	qc_print_jagged_array_recursive
	br      	1                               # 1: down to label181
.LBB94_4:                               #   in Loop: Header=BB94_2 Depth=1
	end_block                               # label182:
	block   	
	local.get	3
	i32.const	1
	i32.ne  
	br_if   	0                               # 0: down to label183
# %bb.5:                                #   in Loop: Header=BB94_2 Depth=1
	local.get	0
	i32.load	0
	local.get	2
	i32.wrap_i64
	i32.const	2
	i32.shl 
	local.tee	4
	i32.add 
	i32.load	0
	local.set	5
	i32.const	91
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	0
	i32.load	8
	local.get	4
	i32.add 
	i32.load	0
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label184
# %bb.6:                                # %.preheader
                                        #   in Loop: Header=BB94_2 Depth=1
	i32.const	0
	local.set	3
.LBB94_7:                               #   Parent Loop BB94_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	loop    	                                # label185:
	i32.const	4
	local.set	6
	block   	
	local.get	0
	i32.load	20
	local.tee	7
	i32.const	-2
	i32.add 
	local.tee	8
	i32.const	4
	i32.gt_u
	br_if   	0                               # 0: down to label186
# %bb.8:                                #   in Loop: Header=BB94_7 Depth=2
	local.get	8
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_stringify_jagged_helper
	local.set	6
.LBB94_9:                               #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label186:
	local.get	5
	local.get	6
	local.get	3
	i32.mul 
	i32.add 
	local.set	6
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	7
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label193
                                        # 2: down to label192
                                        # 3: down to label191
                                        # 4: down to label190
                                        # 5: down to label189
                                        # 6: down to label188
                                        # 7: down to label187
.LBB94_10:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label194:
	local.get	1
	local.get	6
	i32.load	0
	i32.store	0
	i32.const	.L.str.34
	local.get	1
	call	printf
	drop
	br      	6                               # 6: down to label187
.LBB94_11:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label193:
	local.get	1
	local.get	6
	f32.load	0
	f64.promote_f32
	f64.store	16
	i32.const	.L.str.35
	local.get	1
	i32.const	16
	i32.add 
	call	printf
	drop
	br      	5                               # 5: down to label187
.LBB94_12:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label192:
	local.get	1
	local.get	6
	f64.load	0
	f64.store	32
	i32.const	.L.str.35
	local.get	1
	i32.const	32
	i32.add 
	call	printf
	drop
	br      	4                               # 4: down to label187
.LBB94_13:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label191:
	local.get	1
	local.get	6
	i32.load8_s	0
	i32.store	48
	i32.const	.L.str.46
	local.get	1
	i32.const	48
	i32.add 
	call	printf
	drop
	br      	3                               # 3: down to label187
.LBB94_14:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label190:
	local.get	1
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	6
	i32.load8_u	0
	i32.select
	i32.store	64
	i32.const	.L.str.39
	local.get	1
	i32.const	64
	i32.add 
	call	printf
	drop
	br      	2                               # 2: down to label187
.LBB94_15:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label189:
	i32.const	.L.str.26
	local.set	7
	block   	
	block   	
	block   	
	local.get	6
	i32.load8_u	0
	i32.const	3
	i32.and 
	local.tee	6
	br_table 	{2, 1, 0}               # 1: down to label196
                                        # 0: down to label197
.LBB94_16:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label197:
	i32.const	.L.str.28
	i32.const	.L.str.29
	local.get	6
	i32.const	2
	i32.eq  
	i32.select
	local.set	7
	br      	1                               # 1: down to label195
.LBB94_17:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label196:
	i32.const	.L.str.27
	local.set	7
.LBB94_18:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label195:
	local.get	1
	local.get	7
	i32.store	80
	i32.const	.L.str.39
	local.get	1
	i32.const	80
	i32.add 
	call	printf
	drop
	br      	1                               # 1: down to label187
.LBB94_19:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label188:
	local.get	1
	local.get	6
	i32.load	0
	i32.store	96
	i32.const	.L.str.45
	local.get	1
	i32.const	96
	i32.add 
	call	printf
	drop
.LBB94_20:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label187:
	block   	
	local.get	3
	local.get	0
	i32.load	8
	local.get	4
	i32.add 
	i32.load	0
	local.tee	6
	i32.const	-1
	i32.add 
	i32.ge_s
	br_if   	0                               # 0: down to label198
# %bb.21:                               #   in Loop: Header=BB94_7 Depth=2
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
	local.get	0
	i32.load	8
	local.get	4
	i32.add 
	i32.load	0
	local.set	6
.LBB94_22:                              #   in Loop: Header=BB94_7 Depth=2
	end_block                               # label198:
	local.get	3
	i32.const	1
	i32.add 
	local.tee	3
	local.get	6
	i32.lt_s
	br_if   	0                               # 0: up to label185
.LBB94_23:                              #   in Loop: Header=BB94_2 Depth=1
	end_loop
	end_block                               # label184:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	br      	1                               # 1: down to label181
.LBB94_24:                              #   in Loop: Header=BB94_2 Depth=1
	end_block                               # label183:
	i32.const	.L.str.47
	i32.const	0
	call	printf
	drop
.LBB94_25:                              #   in Loop: Header=BB94_2 Depth=1
	end_block                               # label181:
	block   	
	local.get	2
	local.get	0
	i32.load	16
	local.tee	3
	i32.const	-1
	i32.add 
	i64.extend_i32_s
	i64.ge_s
	br_if   	0                               # 0: down to label199
# %bb.26:                               #   in Loop: Header=BB94_2 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
	local.get	0
	i32.load	16
	local.set	3
.LBB94_27:                              #   in Loop: Header=BB94_2 Depth=1
	end_block                               # label199:
	local.get	2
	i64.const	1
	i64.add 
	local.tee	2
	local.get	3
	i64.extend_i32_s
	i64.lt_s
	br_if   	0                               # 0: up to label180
.LBB94_28:
	end_loop
	end_block                               # label179:
	i32.const	93
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	local.get	1
	i32.const	112
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_jagged_array_get,"",@
	.type	qc_jagged_array_get,@function   # -- Begin function qc_jagged_array_get
qc_jagged_array_get:                    # @qc_jagged_array_get
	.functype	qc_jagged_array_get (i32, i32, i32) -> (i32)
	.local  	i32, i32, i32
# %bb.0:
	i32.const	0
	local.set	3
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label200
# %bb.1:
	local.get	2
	i32.eqz
	br_if   	0                               # 0: down to label200
# %bb.2:                                # %.preheader
	local.get	2
	i32.const	-1
	i32.add 
	local.set	2
.LBB95_3:                               # =>This Inner Loop Header: Depth=1
	loop    	                                # label201:
	local.get	2
	local.set	4
	i32.const	0
	local.set	3
	local.get	1
	i32.load	0
	local.tee	2
	i32.const	0
	i32.lt_s
	br_if   	1                               # 1: down to label200
# %bb.4:                                #   in Loop: Header=BB95_3 Depth=1
	local.get	2
	local.get	0
	i32.load	16
	i32.ge_s
	br_if   	1                               # 1: down to label200
# %bb.5:                                #   in Loop: Header=BB95_3 Depth=1
	block   	
	block   	
	block   	
	local.get	0
	i32.load	24
	br_table 	{0, 1, 2}               # 1: down to label203
                                        # 2: down to label202
.LBB95_6:
	end_block                               # label204:
	block   	
	local.get	4
	br_if   	0                               # 0: down to label205
# %bb.7:
	local.get	0
	i32.load	0
	local.get	2
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	return
.LBB95_8:
	end_block                               # label205:
	i32.const	0
	local.set	3
	local.get	1
	i32.const	4
	i32.add 
	i32.load	0
	local.tee	1
	i32.const	0
	i32.lt_s
	br_if   	3                               # 3: down to label200
# %bb.9:
	local.get	1
	local.get	0
	i32.load	8
	local.get	2
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	i32.ge_s
	br_if   	3                               # 3: down to label200
# %bb.10:
	i32.const	4
	local.set	3
	local.get	0
	i32.load	0
	local.get	2
	i64.extend_i32_u
	i32.wrap_i64
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	local.set	2
	block   	
	local.get	0
	i32.load	20
	i32.const	-2
	i32.add 
	local.tee	0
	i32.const	4
	i32.gt_u
	br_if   	0                               # 0: down to label206
# %bb.11:
	local.get	0
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_stringify_jagged_helper
	local.set	3
.LBB95_12:
	end_block                               # label206:
	local.get	2
	local.get	3
	local.get	1
	i32.mul 
	i32.add 
	return
.LBB95_13:
	end_block                               # label203:
	local.get	0
	i32.load	0
	local.get	2
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	local.set	5
	block   	
	local.get	4
	br_if   	0                               # 0: down to label207
# %bb.14:
	local.get	5
	return
.LBB95_15:
	end_block                               # label207:
	i32.const	0
	local.set	3
	local.get	1
	i32.const	4
	i32.add 
	i32.load	0
	local.tee	1
	i32.const	0
	i32.lt_s
	br_if   	2                               # 2: down to label200
# %bb.16:
	local.get	1
	local.get	0
	i32.load	8
	local.get	2
	i64.extend_i32_u
	i32.wrap_i64
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	i32.ge_s
	br_if   	2                               # 2: down to label200
# %bb.17:
	i32.const	4
	local.set	3
	block   	
	local.get	0
	i32.load	20
	i32.const	-2
	i32.add 
	local.tee	0
	i32.const	4
	i32.gt_u
	br_if   	0                               # 0: down to label208
# %bb.18:
	local.get	0
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_stringify_jagged_helper
	local.set	3
.LBB95_19:
	end_block                               # label208:
	local.get	5
	local.get	3
	local.get	1
	i32.mul 
	i32.add 
	return
.LBB95_20:                              #   in Loop: Header=BB95_3 Depth=1
	end_block                               # label202:
	local.get	0
	i32.load	0
	local.get	2
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	local.tee	0
	i32.eqz
	br_if   	1                               # 1: down to label200
# %bb.21:                               #   in Loop: Header=BB95_3 Depth=1
	local.get	4
	i32.const	-1
	i32.add 
	local.set	2
	local.get	1
	i32.const	4
	i32.add 
	local.set	1
	local.get	4
	br_if   	0                               # 0: up to label201
.LBB95_22:
	end_loop
	end_block                               # label200:
	local.get	3
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_create_leaf_row,"",@
	.type	qc_create_leaf_row,@function    # -- Begin function qc_create_leaf_row
qc_create_leaf_row:                     # @qc_create_leaf_row
	.functype	qc_create_leaf_row (i32, i32) -> (i32)
	.local  	i32
# %bb.0:
	i32.const	4
	local.set	2
	block   	
	local.get	1
	i32.const	-2
	i32.add 
	local.tee	1
	i32.const	4
	i32.gt_u
	br_if   	0                               # 0: down to label209
# %bb.1:
	local.get	1
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_stringify_jagged_helper
	local.set	2
.LBB96_2:
	end_block                               # label209:
	local.get	2
	local.get	0
	i32.mul 
	i64.extend_i32_s
	call	malloc
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_set_leaf_element,"",@
	.type	qc_set_leaf_element,@function   # -- Begin function qc_set_leaf_element
qc_set_leaf_element:                    # @qc_set_leaf_element
	.functype	qc_set_leaf_element (i32, i32, i32, i32) -> ()
	.local  	i32, i32, i64
# %bb.0:
	i32.const	4
	local.set	4
	block   	
	local.get	3
	i32.const	-2
	i32.add 
	local.tee	3
	i32.const	4
	i32.gt_u
	local.tee	5
	br_if   	0                               # 0: down to label210
# %bb.1:
	local.get	3
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_stringify_jagged_helper
	local.set	4
.LBB97_2:
	end_block                               # label210:
	i64.const	4
	local.set	6
	block   	
	local.get	5
	br_if   	0                               # 0: down to label211
# %bb.3:
	local.get	3
	i32.const	3
	i32.shl 
	i64.load	.Lswitch.table.qc_set_leaf_element.52
	local.set	6
.LBB97_4:
	end_block                               # label211:
	block   	
	local.get	6
	i32.wrap_i64
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label212
# %bb.5:
	local.get	0
	local.get	4
	local.get	1
	i32.mul 
	i32.add 
	local.get	2
	local.get	3
	memory.copy	0, 0
.LBB97_6:
	end_block                               # label212:
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_stringify_jagged_helper,"",@
	.type	qc_stringify_jagged_helper,@function # -- Begin function qc_stringify_jagged_helper
qc_stringify_jagged_helper:             # @qc_stringify_jagged_helper
	.functype	qc_stringify_jagged_helper (i32, i32, i32, i32, i32) -> ()
	.local  	i32, i32, i64, i32, i32, i32, i32, i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	176
	i32.sub 
	local.tee	5
	global.set	__stack_pointer
	local.get	1
	i32.load	0
	i32.const	91
	i32.store8	0
	local.get	2
	local.get	2
	i32.load	0
	i32.const	-1
	i32.add 
	i32.store	0
	local.get	1
	local.get	1
	i32.load	0
	i32.const	1
	i32.add 
	local.tee	6
	i32.store	0
	block   	
	local.get	0
	i32.load	16
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label213
# %bb.1:
	i64.const	0
	local.set	7
.LBB98_2:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB98_6 Depth 2
	loop    	                                # label214:
	block   	
	block   	
	local.get	0
	i32.load	24
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label216
# %bb.3:                                #   in Loop: Header=BB98_2 Depth=1
	local.get	0
	i32.load	0
	local.get	7
	i32.wrap_i64
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	local.get	1
	local.get	2
	local.get	3
	local.get	4
	call	qc_stringify_jagged_helper
	br      	1                               # 1: down to label215
.LBB98_4:                               #   in Loop: Header=BB98_2 Depth=1
	end_block                               # label216:
	local.get	1
	i32.load	0
	i32.const	91
	i32.store8	0
	local.get	2
	local.get	2
	i32.load	0
	i32.const	-1
	i32.add 
	i32.store	0
	local.get	1
	local.get	1
	i32.load	0
	i32.const	1
	i32.add 
	local.tee	8
	i32.store	0
	block   	
	local.get	0
	i32.load	8
	local.get	7
	i32.wrap_i64
	i32.const	2
	i32.shl 
	local.tee	9
	i32.add 
	i32.load	0
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label217
# %bb.5:                                # %.preheader
                                        #   in Loop: Header=BB98_2 Depth=1
	local.get	0
	i32.load	0
	local.get	9
	i32.add 
	i32.load	0
	local.set	10
	i32.const	0
	local.set	6
.LBB98_6:                               #   Parent Loop BB98_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	loop    	                                # label218:
	i32.const	4
	local.set	11
	block   	
	local.get	0
	i32.load	20
	local.tee	8
	i32.const	-2
	i32.add 
	local.tee	12
	i32.const	4
	i32.gt_u
	br_if   	0                               # 0: down to label219
# %bb.7:                                #   in Loop: Header=BB98_6 Depth=2
	local.get	12
	i32.const	2
	i32.shl 
	i32.load	.Lswitch.table.qc_stringify_jagged_helper
	local.set	11
.LBB98_8:                               #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label219:
	local.get	10
	local.get	11
	local.get	6
	i32.mul 
	i32.add 
	local.set	11
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	8
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label226
                                        # 2: down to label225
                                        # 3: down to label224
                                        # 4: down to label223
                                        # 5: down to label222
                                        # 6: down to label221
                                        # 7: down to label220
.LBB98_9:                               #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label227:
	local.get	5
	local.get	11
	i32.load	0
	i32.store	0
	local.get	5
	i32.const	112
	i32.add 
	i64.const	64
	i32.const	.L.str.34
	local.get	5
	call	snprintf
	drop
	br      	6                               # 6: down to label220
.LBB98_10:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label226:
	local.get	5
	local.get	11
	f32.load	0
	f64.promote_f32
	f64.store	16
	local.get	5
	i32.const	112
	i32.add 
	i64.const	64
	i32.const	.L.str.35
	local.get	5
	i32.const	16
	i32.add 
	call	snprintf
	drop
	br      	5                               # 5: down to label220
.LBB98_11:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label225:
	local.get	5
	local.get	11
	f64.load	0
	f64.store	32
	local.get	5
	i32.const	112
	i32.add 
	i64.const	64
	i32.const	.L.str.35
	local.get	5
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	4                               # 4: down to label220
.LBB98_12:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label224:
	local.get	5
	local.get	11
	i32.load8_s	0
	i32.store	48
	local.get	5
	i32.const	112
	i32.add 
	i64.const	64
	i32.const	.L.str.46
	local.get	5
	i32.const	48
	i32.add 
	call	snprintf
	drop
	br      	3                               # 3: down to label220
.LBB98_13:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label223:
	local.get	5
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	11
	i32.load8_u	0
	i32.select
	i32.store	64
	local.get	5
	i32.const	112
	i32.add 
	i64.const	64
	i32.const	.L.str.39
	local.get	5
	i32.const	64
	i32.add 
	call	snprintf
	drop
	br      	2                               # 2: down to label220
.LBB98_14:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label222:
	i32.const	.L.str.26
	local.set	8
	block   	
	block   	
	block   	
	local.get	11
	i32.load8_u	0
	i32.const	3
	i32.and 
	local.tee	11
	br_table 	{2, 1, 0}               # 1: down to label229
                                        # 0: down to label230
.LBB98_15:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label230:
	i32.const	.L.str.28
	i32.const	.L.str.29
	local.get	11
	i32.const	2
	i32.eq  
	i32.select
	local.set	8
	br      	1                               # 1: down to label228
.LBB98_16:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label229:
	i32.const	.L.str.27
	local.set	8
.LBB98_17:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label228:
	local.get	5
	local.get	8
	i32.store	80
	local.get	5
	i32.const	112
	i32.add 
	i64.const	64
	i32.const	.L.str.39
	local.get	5
	i32.const	80
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label220
.LBB98_18:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label221:
	local.get	5
	local.get	11
	i32.load	0
	i32.store	96
	local.get	5
	i32.const	112
	i32.add 
	i64.const	64
	i32.const	.L.str.45
	local.get	5
	i32.const	96
	i32.add 
	call	snprintf
	drop
.LBB98_19:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label220:
	local.get	1
	i32.load	0
	local.set	11
	block   	
	local.get	2
	i32.load	0
	local.get	5
	i32.const	112
	i32.add 
	call	strlen
	i32.wrap_i64
	local.tee	8
	i32.const	10
	i32.add 
	i32.ge_s
	br_if   	0                               # 0: down to label231
# %bb.20:                               #   in Loop: Header=BB98_6 Depth=2
	local.get	3
	local.get	3
	i32.load	0
	i32.const	1
	i32.shl 
	local.tee	12
	i32.store	0
	local.get	4
	local.get	4
	i32.load	0
	local.tee	13
	local.get	12
	i64.extend_i32_s
	call	realloc
	local.tee	12
	i32.store	0
	local.get	1
	local.get	12
	local.get	11
	i64.extend_i32_u
	local.get	13
	i64.extend_i32_u
	i64.sub 
	i32.wrap_i64
	local.tee	13
	i32.add 
	local.tee	11
	i32.store	0
	local.get	2
	local.get	3
	i32.load	0
	local.get	13
	i32.sub 
	i32.store	0
.LBB98_21:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label231:
	local.get	11
	local.get	5
	i32.const	112
	i32.add 
	call	strcpy
	drop
	local.get	2
	local.get	2
	i32.load	0
	local.get	8
	i32.sub 
	i32.store	0
	local.get	1
	local.get	1
	i32.load	0
	local.get	8
	i32.add 
	local.tee	8
	i32.store	0
	block   	
	local.get	6
	local.get	0
	i32.load	8
	local.get	9
	i32.add 
	i32.load	0
	local.tee	11
	i32.const	-1
	i32.add 
	i32.ge_s
	br_if   	0                               # 0: down to label232
# %bb.22:                               #   in Loop: Header=BB98_6 Depth=2
	local.get	8
	i32.const	44
	i32.store8	0
	local.get	1
	local.get	1
	i32.load	0
	local.tee	11
	i32.const	1
	i32.add 
	i32.store	0
	local.get	11
	i32.const	32
	i32.store8	1
	local.get	2
	local.get	2
	i32.load	0
	i32.const	-2
	i32.add 
	i32.store	0
	local.get	1
	local.get	1
	i32.load	0
	i32.const	1
	i32.add 
	local.tee	8
	i32.store	0
	local.get	0
	i32.load	8
	local.get	9
	i32.add 
	i32.load	0
	local.set	11
.LBB98_23:                              #   in Loop: Header=BB98_6 Depth=2
	end_block                               # label232:
	local.get	6
	i32.const	1
	i32.add 
	local.tee	6
	local.get	11
	i32.lt_s
	br_if   	0                               # 0: up to label218
.LBB98_24:                              #   in Loop: Header=BB98_2 Depth=1
	end_loop
	end_block                               # label217:
	local.get	8
	i32.const	93
	i32.store8	0
	local.get	1
	local.get	1
	i32.load	0
	i32.const	1
	i32.add 
	i32.store	0
	local.get	2
	local.get	2
	i32.load	0
	i32.const	-1
	i32.add 
	i32.store	0
.LBB98_25:                              #   in Loop: Header=BB98_2 Depth=1
	end_block                               # label215:
	block   	
	local.get	7
	local.get	0
	i32.load	16
	local.tee	6
	i32.const	-1
	i32.add 
	i64.extend_i32_s
	i64.ge_s
	br_if   	0                               # 0: down to label233
# %bb.26:                               #   in Loop: Header=BB98_2 Depth=1
	local.get	1
	i32.load	0
	i32.const	44
	i32.store8	0
	local.get	1
	local.get	1
	i32.load	0
	local.tee	6
	i32.const	1
	i32.add 
	i32.store	0
	local.get	6
	i32.const	32
	i32.store8	1
	local.get	2
	local.get	2
	i32.load	0
	i32.const	-2
	i32.add 
	i32.store	0
	local.get	1
	local.get	1
	i32.load	0
	i32.const	1
	i32.add 
	i32.store	0
	local.get	0
	i32.load	16
	local.set	6
.LBB98_27:                              #   in Loop: Header=BB98_2 Depth=1
	end_block                               # label233:
	local.get	7
	i64.const	1
	i64.add 
	local.tee	7
	local.get	6
	i64.extend_i32_s
	i64.lt_s
	br_if   	0                               # 0: up to label214
# %bb.28:
	end_loop
	local.get	1
	i32.load	0
	local.set	6
.LBB98_29:
	end_block                               # label213:
	local.get	6
	i32.const	93
	i32.store8	0
	local.get	1
	local.get	1
	i32.load	0
	i32.const	1
	i32.add 
	i32.store	0
	local.get	2
	local.get	2
	i32.load	0
	i32.const	-1
	i32.add 
	i32.store	0
	local.get	5
	i32.const	176
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_jagged_to_string,"",@
	.type	qc_jagged_to_string,@function   # -- Begin function qc_jagged_to_string
qc_jagged_to_string:                    # @qc_jagged_to_string
	.functype	qc_jagged_to_string (i32) -> (i32)
	.local  	i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	32
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	local.get	1
	i32.const	1024
	i32.store	28
	local.get	1
	i64.const	1024
	call	malloc
	local.tee	2
	i32.store	24
	local.get	1
	local.get	2
	i32.store	16
	local.get	1
	i32.const	1024
	i32.store	12
	local.get	0
	local.get	1
	i32.const	16
	i32.add 
	local.get	1
	i32.const	12
	i32.add 
	local.get	1
	i32.const	28
	i32.add 
	local.get	1
	i32.const	24
	i32.add 
	call	qc_stringify_jagged_helper
	local.get	1
	i32.load	16
	i32.const	0
	i32.store8	0
	local.get	1
	i32.load	24
	local.set	0
	local.get	1
	i32.const	32
	i32.add 
	global.set	__stack_pointer
	local.get	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_create_list,"",@
	.type	qc_create_list,@function        # -- Begin function qc_create_list
qc_create_list:                         # @qc_create_list
	.functype	qc_create_list (i32) -> (i32)
	.local  	i32
# %bb.0:
	i64.const	24
	call	malloc
	local.tee	1
	local.get	0
	i32.store	16
	local.get	1
	i64.const	17179869184
	i64.store	8
	local.get	1
	i64.const	32
	call	malloc
	i32.store	0
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_list_push,"",@
	.type	qc_list_push,@function          # -- Begin function qc_list_push
qc_list_push:                           # @qc_list_push
	.functype	qc_list_push (i32, i32, i32) -> ()
	.local  	i32, i64
# %bb.0:
	block   	
	local.get	0
	i32.load	8
	local.get	0
	i32.load	12
	local.tee	3
	i32.lt_s
	br_if   	0                               # 0: down to label234
# %bb.1:
	local.get	0
	local.get	3
	i32.const	1
	i32.shl 
	local.tee	3
	i32.store	12
	local.get	0
	local.get	0
	i32.load	0
	local.get	3
	i64.extend_i32_s
	i64.const	3
	i64.shl 
	call	realloc
	i32.store	0
.LBB101_2:
	end_block                               # label234:
	block   	
	block   	
	local.get	2
	i32.const	5
	i32.gt_s
	br_if   	0                               # 0: down to label236
# %bb.3:
	i64.const	4
	local.set	4
	block   	
	local.get	2
	i32.const	-2
	i32.add 
	local.tee	2
	i32.const	3
	i32.gt_u
	br_if   	0                               # 0: down to label237
# %bb.4:
	local.get	2
	i32.const	3
	i32.shl 
	i64.load	.Lswitch.table.qc_map_set.54
	local.set	4
.LBB101_5:
	end_block                               # label237:
	local.get	4
	call	malloc
	local.set	2
	local.get	4
	i32.wrap_i64
	local.tee	3
	i32.eqz
	br_if   	1                               # 1: down to label235
# %bb.6:
	local.get	2
	local.get	1
	local.get	3
	memory.copy	0, 0
	br      	1                               # 1: down to label235
.LBB101_7:
	end_block                               # label236:
	local.get	1
	i32.load	0
	local.set	2
.LBB101_8:
	end_block                               # label235:
	local.get	0
	local.get	0
	i32.load	8
	local.tee	1
	i32.const	1
	i32.add 
	i32.store	8
	local.get	0
	i32.load	0
	local.get	1
	i32.const	2
	i32.shl 
	i32.add 
	local.get	2
	i32.store	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_list_set,"",@
	.type	qc_list_set,@function           # -- Begin function qc_list_set
qc_list_set:                            # @qc_list_set
	.functype	qc_list_set (i32, i32, i32) -> ()
	.local  	i32, i64, i32
# %bb.0:
	block   	
	local.get	1
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label238
# %bb.1:
	local.get	1
	local.get	0
	i32.load	8
	i32.ge_s
	br_if   	0                               # 0: down to label238
# %bb.2:
	block   	
	local.get	0
	i32.load	16
	local.tee	3
	i32.const	5
	i32.gt_s
	br_if   	0                               # 0: down to label239
# %bb.3:
	i64.const	4
	local.set	4
	block   	
	local.get	3
	i32.const	-2
	i32.add 
	local.tee	3
	i32.const	3
	i32.gt_u
	br_if   	0                               # 0: down to label240
# %bb.4:
	local.get	3
	i32.const	3
	i32.shl 
	i64.load	.Lswitch.table.qc_map_set.54
	local.set	4
.LBB102_5:
	end_block                               # label240:
	local.get	4
	call	malloc
	local.set	3
	block   	
	local.get	4
	i32.wrap_i64
	local.tee	5
	i32.eqz
	br_if   	0                               # 0: down to label241
# %bb.6:
	local.get	3
	local.get	2
	local.get	5
	memory.copy	0, 0
.LBB102_7:
	end_block                               # label241:
	local.get	0
	i32.load	0
	local.get	1
	i32.const	2
	i32.shl 
	local.tee	1
	i32.add 
	i32.load	0
	call	free
	local.get	0
	i32.load	0
	local.get	1
	i32.add 
	local.get	3
	i32.store	0
	return
.LBB102_8:
	end_block                               # label239:
	local.get	0
	i32.load	0
	local.get	1
	i32.const	2
	i32.shl 
	i32.add 
	local.get	2
	i32.load	0
	i32.store	0
.LBB102_9:
	end_block                               # label238:
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_list_get,"",@
	.type	qc_list_get,@function           # -- Begin function qc_list_get
qc_list_get:                            # @qc_list_get
	.functype	qc_list_get (i32, i32) -> (i32)
	.local  	i32
# %bb.0:
	i32.const	0
	local.set	2
	block   	
	local.get	1
	i32.const	0
	i32.lt_s
	br_if   	0                               # 0: down to label242
# %bb.1:
	local.get	1
	local.get	0
	i32.load	8
	i32.ge_s
	br_if   	0                               # 0: down to label242
# %bb.2:
	local.get	0
	i32.load	0
	local.get	1
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	local.set	2
.LBB103_3:
	end_block                               # label242:
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_list_pop,"",@
	.type	qc_list_pop,@function           # -- Begin function qc_list_pop
qc_list_pop:                            # @qc_list_pop
	.functype	qc_list_pop (i32) -> (i32)
	.local  	i32
# %bb.0:
	block   	
	local.get	0
	i32.load	8
	local.tee	1
	br_if   	0                               # 0: down to label243
# %bb.1:
	i32.const	0
	return
.LBB104_2:
	end_block                               # label243:
	local.get	0
	local.get	1
	i32.const	-1
	i32.add 
	local.tee	1
	i32.store	8
	local.get	0
	i32.load	0
	local.get	1
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_list_length,"",@
	.type	qc_list_length,@function        # -- Begin function qc_list_length
qc_list_length:                         # @qc_list_length
	.functype	qc_list_length (i32) -> (i32)
# %bb.0:
	local.get	0
	i32.load	8
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_create_map,"",@
	.type	qc_create_map,@function         # -- Begin function qc_create_map
qc_create_map:                          # @qc_create_map
	.functype	qc_create_map (i32, i32) -> (i32)
	.local  	i32
# %bb.0:
	i64.const	32
	call	malloc
	local.tee	2
	local.get	1
	i32.store	28
	local.get	2
	local.get	0
	i32.store	24
	local.get	2
	i64.const	17179869184
	i64.store	16
	local.get	2
	i64.const	32
	call	malloc
	i32.store	0
	local.get	2
	i64.const	32
	call	malloc
	i32.store	8
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_compare_keys,"",@
	.type	qc_compare_keys,@function       # -- Begin function qc_compare_keys
qc_compare_keys:                        # @qc_compare_keys
	.functype	qc_compare_keys (i32, i32, i32) -> (i32)
	.local  	i32
# %bb.0:
	i32.const	0
	local.set	3
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label244
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label244
# %bb.2:
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	2
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label250
                                        # 2: down to label249
                                        # 3: down to label248
                                        # 4: down to label247
                                        # 5: down to label246
                                        # 6: down to label245
                                        # 7: down to label244
.LBB107_3:
	end_block                               # label251:
	local.get	0
	i32.load	0
	local.get	1
	i32.load	0
	i32.eq  
	return
.LBB107_4:
	end_block                               # label250:
	local.get	0
	f32.load	0
	local.get	1
	f32.load	0
	f32.eq  
	return
.LBB107_5:
	end_block                               # label249:
	local.get	0
	f64.load	0
	local.get	1
	f64.load	0
	f64.eq  
	return
.LBB107_6:
	end_block                               # label248:
	local.get	0
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	return
.LBB107_7:
	end_block                               # label247:
	local.get	0
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	return
.LBB107_8:
	end_block                               # label246:
	local.get	0
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	return
.LBB107_9:
	end_block                               # label245:
	local.get	0
	local.get	1
	call	strcmp
	i32.eqz
	local.set	3
.LBB107_10:
	end_block                               # label244:
	local.get	3
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_map_set,"",@
	.type	qc_map_set,@function            # -- Begin function qc_map_set
qc_map_set:                             # @qc_map_set
	.functype	qc_map_set (i32, i32, i32) -> ()
	.local  	i32, i32, i32, i64, i64, i32, i32
# %bb.0:
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	16
	local.tee	3
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label260
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label260
# %bb.2:
	local.get	0
	i32.load	0
	local.set	4
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	24
	local.tee	5
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label266
                                        # 2: down to label265
                                        # 3: down to label264
                                        # 4: down to label263
                                        # 5: down to label262
                                        # 6: down to label261
                                        # 7: down to label260
.LBB108_3:
	end_block                               # label267:
	local.get	3
	i64.extend_i32_u
	local.set	6
	i64.const	0
	local.set	7
	local.get	4
	local.set	8
.LBB108_4:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label268:
	block   	
	local.get	8
	i32.load	0
	local.tee	9
	i32.eqz
	br_if   	0                               # 0: down to label269
# %bb.5:                                #   in Loop: Header=BB108_4 Depth=1
	local.get	9
	i32.load	0
	local.get	1
	i32.load	0
	i32.eq  
	br_if   	10                              # 10: down to label258
.LBB108_6:                              #   in Loop: Header=BB108_4 Depth=1
	end_block                               # label269:
	local.get	8
	i32.const	4
	i32.add 
	local.set	8
	local.get	6
	local.get	7
	i64.const	1
	i64.add 
	local.tee	7
	i64.ne  
	br_if   	0                               # 0: up to label268
	br      	7                               # 7: down to label260
.LBB108_7:
	end_loop
	end_block                               # label266:
	local.get	3
	i64.extend_i32_u
	local.set	6
	i64.const	0
	local.set	7
	local.get	4
	local.set	8
.LBB108_8:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label270:
	block   	
	local.get	8
	i32.load	0
	local.tee	9
	i32.eqz
	br_if   	0                               # 0: down to label271
# %bb.9:                                #   in Loop: Header=BB108_8 Depth=1
	local.get	9
	f32.load	0
	local.get	1
	f32.load	0
	f32.eq  
	br_if   	9                               # 9: down to label258
.LBB108_10:                             #   in Loop: Header=BB108_8 Depth=1
	end_block                               # label271:
	local.get	8
	i32.const	4
	i32.add 
	local.set	8
	local.get	6
	local.get	7
	i64.const	1
	i64.add 
	local.tee	7
	i64.ne  
	br_if   	0                               # 0: up to label270
	br      	6                               # 6: down to label260
.LBB108_11:
	end_loop
	end_block                               # label265:
	local.get	3
	i64.extend_i32_u
	local.set	6
	i64.const	0
	local.set	7
	local.get	4
	local.set	8
.LBB108_12:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label272:
	block   	
	local.get	8
	i32.load	0
	local.tee	9
	i32.eqz
	br_if   	0                               # 0: down to label273
# %bb.13:                               #   in Loop: Header=BB108_12 Depth=1
	local.get	9
	f64.load	0
	local.get	1
	f64.load	0
	f64.eq  
	br_if   	8                               # 8: down to label258
.LBB108_14:                             #   in Loop: Header=BB108_12 Depth=1
	end_block                               # label273:
	local.get	8
	i32.const	4
	i32.add 
	local.set	8
	local.get	6
	local.get	7
	i64.const	1
	i64.add 
	local.tee	7
	i64.ne  
	br_if   	0                               # 0: up to label272
	br      	5                               # 5: down to label260
.LBB108_15:
	end_loop
	end_block                               # label264:
	local.get	3
	i64.extend_i32_u
	local.set	6
	i64.const	0
	local.set	7
	local.get	4
	local.set	8
.LBB108_16:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label274:
	block   	
	local.get	8
	i32.load	0
	local.tee	9
	i32.eqz
	br_if   	0                               # 0: down to label275
# %bb.17:                               #   in Loop: Header=BB108_16 Depth=1
	local.get	9
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	br_if   	7                               # 7: down to label258
.LBB108_18:                             #   in Loop: Header=BB108_16 Depth=1
	end_block                               # label275:
	local.get	8
	i32.const	4
	i32.add 
	local.set	8
	local.get	6
	local.get	7
	i64.const	1
	i64.add 
	local.tee	7
	i64.ne  
	br_if   	0                               # 0: up to label274
	br      	4                               # 4: down to label260
.LBB108_19:
	end_loop
	end_block                               # label263:
	local.get	3
	i64.extend_i32_u
	local.set	6
	i64.const	0
	local.set	7
	local.get	4
	local.set	8
.LBB108_20:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label276:
	block   	
	local.get	8
	i32.load	0
	local.tee	9
	i32.eqz
	br_if   	0                               # 0: down to label277
# %bb.21:                               #   in Loop: Header=BB108_20 Depth=1
	local.get	9
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	br_if   	6                               # 6: down to label258
.LBB108_22:                             #   in Loop: Header=BB108_20 Depth=1
	end_block                               # label277:
	local.get	8
	i32.const	4
	i32.add 
	local.set	8
	local.get	6
	local.get	7
	i64.const	1
	i64.add 
	local.tee	7
	i64.ne  
	br_if   	0                               # 0: up to label276
	br      	3                               # 3: down to label260
.LBB108_23:
	end_loop
	end_block                               # label262:
	local.get	3
	i64.extend_i32_u
	local.set	6
	i64.const	0
	local.set	7
	local.get	4
	local.set	8
.LBB108_24:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label278:
	block   	
	local.get	8
	i32.load	0
	local.tee	9
	i32.eqz
	br_if   	0                               # 0: down to label279
# %bb.25:                               #   in Loop: Header=BB108_24 Depth=1
	local.get	9
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	br_if   	5                               # 5: down to label258
.LBB108_26:                             #   in Loop: Header=BB108_24 Depth=1
	end_block                               # label279:
	local.get	8
	i32.const	4
	i32.add 
	local.set	8
	local.get	6
	local.get	7
	i64.const	1
	i64.add 
	local.tee	7
	i64.ne  
	br_if   	0                               # 0: up to label278
	br      	2                               # 2: down to label260
.LBB108_27:
	end_loop
	end_block                               # label261:
	local.get	3
	i64.extend_i32_u
	local.set	6
	i64.const	0
	local.set	7
	local.get	4
	local.set	8
.LBB108_28:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label280:
	block   	
	local.get	8
	i32.load	0
	local.tee	9
	i32.eqz
	br_if   	0                               # 0: down to label281
# %bb.29:                               #   in Loop: Header=BB108_28 Depth=1
	local.get	9
	local.get	1
	call	strcmp
	i32.eqz
	br_if   	3                               # 3: down to label259
.LBB108_30:                             #   in Loop: Header=BB108_28 Depth=1
	end_block                               # label281:
	local.get	8
	i32.const	4
	i32.add 
	local.set	8
	local.get	6
	local.get	7
	i64.const	1
	i64.add 
	local.tee	7
	i64.ne  
	br_if   	0                               # 0: up to label280
.LBB108_31:
	end_loop
	end_block                               # label260:
	block   	
	local.get	3
	local.get	0
	i32.load	20
	local.tee	8
	i32.lt_s
	br_if   	0                               # 0: down to label282
# %bb.32:
	local.get	0
	local.get	8
	i32.const	1
	i32.shl 
	local.tee	8
	i32.store	20
	local.get	0
	local.get	0
	i32.load	0
	local.get	8
	i64.extend_i32_s
	i64.const	3
	i64.shl 
	call	realloc
	i32.store	0
	local.get	0
	local.get	0
	i32.load	8
	local.get	0
	i64.load32_s	20
	i64.const	3
	i64.shl 
	call	realloc
	i32.store	8
.LBB108_33:
	end_block                               # label282:
	local.get	0
	i32.load	24
	local.tee	8
	i32.const	5
	i32.gt_s
	br_if   	4                               # 4: down to label255
# %bb.34:
	i64.const	4
	local.set	7
	block   	
	local.get	8
	i32.const	-2
	i32.add 
	local.tee	8
	i32.const	3
	i32.gt_u
	br_if   	0                               # 0: down to label283
# %bb.35:
	local.get	8
	i32.const	3
	i32.shl 
	i64.load	.Lswitch.table.qc_map_set.54
	local.set	7
.LBB108_36:
	end_block                               # label283:
	local.get	7
	call	malloc
	local.set	8
	local.get	7
	i32.wrap_i64
	local.tee	3
	i32.eqz
	br_if   	5                               # 5: down to label254
# %bb.37:
	local.get	8
	local.get	1
	local.get	3
	memory.copy	0, 0
	br      	5                               # 5: down to label254
.LBB108_38:
	end_block                               # label259:
	local.get	0
	i32.load	28
	local.tee	8
	i32.const	5
	i32.gt_s
	br_if   	1                               # 1: down to label257
	br      	5                               # 5: down to label253
.LBB108_39:
	end_block                               # label258:
	local.get	0
	i32.load	28
	local.tee	8
	i32.const	6
	i32.lt_s
	br_if   	4                               # 4: down to label253
# %bb.40:
	local.get	5
	i32.const	6
	i32.ne  
	br_if   	1                               # 1: down to label256
# %bb.41:
	local.get	3
	i64.extend_i32_u
	local.set	6
.LBB108_42:
	end_block                               # label257:
	local.get	4
	local.get	6
	i32.wrap_i64
	i32.const	2
	i32.shl 
	i32.add 
	local.get	1
	call	strdup
	i32.store	0
	return
.LBB108_43:
	end_block                               # label256:
	local.get	0
	i32.load	8
	local.get	7
	i32.wrap_i64
	i32.const	2
	i32.shl 
	i32.add 
	local.get	2
	i32.store	0
	return
.LBB108_44:
	end_block                               # label255:
	block   	
	local.get	8
	i32.const	6
	i32.eq  
	br_if   	0                               # 0: down to label284
# %bb.45:
	local.get	1
	local.set	8
	br      	1                               # 1: down to label254
.LBB108_46:
	end_block                               # label284:
	local.get	1
	call	strdup
	local.set	8
.LBB108_47:
	end_block                               # label254:
	local.get	0
	i32.load	0
	local.get	0
	i32.load	16
	local.tee	1
	i32.const	2
	i32.shl 
	i32.add 
	local.get	8
	i32.store	0
	block   	
	block   	
	local.get	0
	i32.load	28
	local.tee	8
	i32.const	5
	i32.gt_s
	br_if   	0                               # 0: down to label286
# %bb.48:
	i64.const	4
	local.set	7
	block   	
	local.get	8
	i32.const	-2
	i32.add 
	local.tee	8
	i32.const	3
	i32.gt_u
	br_if   	0                               # 0: down to label287
# %bb.49:
	local.get	8
	i32.const	3
	i32.shl 
	i64.load	.Lswitch.table.qc_map_set.54
	local.set	7
.LBB108_50:
	end_block                               # label287:
	local.get	7
	call	malloc
	local.set	8
	local.get	7
	i32.wrap_i64
	local.tee	3
	i32.eqz
	br_if   	1                               # 1: down to label285
# %bb.51:
	local.get	8
	local.get	2
	local.get	3
	memory.copy	0, 0
	br      	1                               # 1: down to label285
.LBB108_52:
	end_block                               # label286:
	block   	
	local.get	8
	i32.const	6
	i32.eq  
	br_if   	0                               # 0: down to label288
# %bb.53:
	local.get	2
	local.set	8
	br      	1                               # 1: down to label285
.LBB108_54:
	end_block                               # label288:
	local.get	2
	call	strdup
	local.set	8
.LBB108_55:
	end_block                               # label285:
	local.get	0
	local.get	1
	i32.const	1
	i32.add 
	i32.store	16
	local.get	0
	i32.load	8
	local.get	1
	i32.const	2
	i32.shl 
	i32.add 
	local.get	8
	i32.store	0
	br      	1                               # 1: down to label252
.LBB108_56:
	end_block                               # label253:
	i64.const	4
	local.set	6
	block   	
	local.get	8
	i32.const	-2
	i32.add 
	local.tee	1
	i32.const	3
	i32.gt_u
	br_if   	0                               # 0: down to label289
# %bb.57:
	local.get	1
	i32.const	3
	i32.shl 
	i64.load	.Lswitch.table.qc_map_set.54
	local.set	6
.LBB108_58:
	end_block                               # label289:
	block   	
	local.get	0
	i32.load	8
	local.get	7
	i32.wrap_i64
	i32.const	2
	i32.shl 
	local.tee	8
	i32.add 
	local.tee	3
	i32.load	0
	local.tee	1
	br_if   	0                               # 0: down to label290
# %bb.59:
	local.get	3
	local.get	6
	call	malloc
	i32.store	0
	local.get	0
	i32.load	8
	local.get	8
	i32.add 
	i32.load	0
	local.set	1
.LBB108_60:
	end_block                               # label290:
	local.get	6
	i32.wrap_i64
	local.tee	0
	i32.eqz
	br_if   	0                               # 0: down to label252
# %bb.61:
	local.get	1
	local.get	2
	local.get	0
	memory.copy	0, 0
	return
.LBB108_62:
	end_block                               # label252:
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_map_get,"",@
	.type	qc_map_get,@function            # -- Begin function qc_map_get
qc_map_get:                             # @qc_map_get
	.functype	qc_map_get (i32, i32) -> (i32)
	.local  	i32, i32, i32, i64
# %bb.0:
	i32.const	0
	local.set	2
	block   	
	block   	
	local.get	0
	i32.load	16
	local.tee	3
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label292
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label292
# %bb.2:
	local.get	0
	i32.load	0
	local.set	4
	local.get	3
	i64.extend_i32_u
	local.set	5
	i32.const	0
	local.set	2
.LBB109_3:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label293:
	block   	
	local.get	4
	local.get	2
	i32.add 
	i32.load	0
	local.tee	3
	i32.eqz
	br_if   	0                               # 0: down to label294
# %bb.4:                                #   in Loop: Header=BB109_3 Depth=1
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	24
	br_table 	{6, 0, 1, 2, 3, 4, 5, 7} # 0: down to label301
                                        # 1: down to label300
                                        # 2: down to label299
                                        # 3: down to label298
                                        # 4: down to label297
                                        # 5: down to label296
                                        # 7: down to label294
.LBB109_5:                              #   in Loop: Header=BB109_3 Depth=1
	end_block                               # label301:
	local.get	3
	f32.load	0
	local.get	1
	f32.load	0
	f32.eq  
	br_if   	9                               # 9: down to label291
	br      	6                               # 6: down to label294
.LBB109_6:                              #   in Loop: Header=BB109_3 Depth=1
	end_block                               # label300:
	local.get	3
	f64.load	0
	local.get	1
	f64.load	0
	f64.eq  
	br_if   	8                               # 8: down to label291
	br      	5                               # 5: down to label294
.LBB109_7:                              #   in Loop: Header=BB109_3 Depth=1
	end_block                               # label299:
	local.get	3
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	br_if   	7                               # 7: down to label291
	br      	4                               # 4: down to label294
.LBB109_8:                              #   in Loop: Header=BB109_3 Depth=1
	end_block                               # label298:
	local.get	3
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	br_if   	6                               # 6: down to label291
	br      	3                               # 3: down to label294
.LBB109_9:                              #   in Loop: Header=BB109_3 Depth=1
	end_block                               # label297:
	local.get	3
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	br_if   	5                               # 5: down to label291
	br      	2                               # 2: down to label294
.LBB109_10:                             #   in Loop: Header=BB109_3 Depth=1
	end_block                               # label296:
	local.get	3
	local.get	1
	call	strcmp
	br_if   	1                               # 1: down to label294
	br      	4                               # 4: down to label291
.LBB109_11:                             #   in Loop: Header=BB109_3 Depth=1
	end_block                               # label295:
	local.get	3
	i32.load	0
	local.get	1
	i32.load	0
	i32.eq  
	br_if   	3                               # 3: down to label291
.LBB109_12:                             #   in Loop: Header=BB109_3 Depth=1
	end_block                               # label294:
	local.get	2
	i32.const	4
	i32.add 
	local.set	2
	local.get	5
	i64.const	-1
	i64.add 
	local.tee	5
	i64.const	0
	i64.ne  
	br_if   	0                               # 0: up to label293
# %bb.13:
	end_loop
	i32.const	0
	local.set	2
.LBB109_14:
	end_block                               # label292:
	local.get	2
	return
.LBB109_15:
	end_block                               # label291:
	local.get	0
	i32.load	8
	local.get	2
	i32.add 
	i32.load	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_map_has,"",@
	.type	qc_map_has,@function            # -- Begin function qc_map_has
qc_map_has:                             # @qc_map_has
	.functype	qc_map_has (i32, i32) -> (i32)
	.local  	i32, i32, i64
# %bb.0:
	block   	
	local.get	0
	i32.load	16
	local.tee	2
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label302
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label302
# %bb.2:
	local.get	0
	i32.load	0
	local.set	3
	local.get	2
	i64.extend_i32_u
	local.set	4
.LBB110_3:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label303:
	block   	
	local.get	3
	i32.load	0
	local.tee	2
	i32.eqz
	br_if   	0                               # 0: down to label304
# %bb.4:                                #   in Loop: Header=BB110_3 Depth=1
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	24
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label310
                                        # 2: down to label309
                                        # 3: down to label308
                                        # 4: down to label307
                                        # 5: down to label306
                                        # 6: down to label305
                                        # 7: down to label304
.LBB110_5:                              #   in Loop: Header=BB110_3 Depth=1
	end_block                               # label311:
	local.get	2
	i32.load	0
	local.get	1
	i32.load	0
	i32.ne  
	br_if   	6                               # 6: down to label304
# %bb.6:
	i32.const	1
	return
.LBB110_7:                              #   in Loop: Header=BB110_3 Depth=1
	end_block                               # label310:
	local.get	2
	f32.load	0
	local.get	1
	f32.load	0
	f32.ne  
	br_if   	5                               # 5: down to label304
# %bb.8:
	i32.const	1
	return
.LBB110_9:                              #   in Loop: Header=BB110_3 Depth=1
	end_block                               # label309:
	local.get	2
	f64.load	0
	local.get	1
	f64.load	0
	f64.ne  
	br_if   	4                               # 4: down to label304
# %bb.10:
	i32.const	1
	return
.LBB110_11:                             #   in Loop: Header=BB110_3 Depth=1
	end_block                               # label308:
	local.get	2
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.ne  
	br_if   	3                               # 3: down to label304
# %bb.12:
	i32.const	1
	return
.LBB110_13:                             #   in Loop: Header=BB110_3 Depth=1
	end_block                               # label307:
	local.get	2
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.ne  
	br_if   	2                               # 2: down to label304
# %bb.14:
	i32.const	1
	return
.LBB110_15:                             #   in Loop: Header=BB110_3 Depth=1
	end_block                               # label306:
	local.get	2
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.ne  
	br_if   	1                               # 1: down to label304
# %bb.16:
	i32.const	1
	return
.LBB110_17:                             #   in Loop: Header=BB110_3 Depth=1
	end_block                               # label305:
	local.get	2
	local.get	1
	call	strcmp
	br_if   	0                               # 0: down to label304
# %bb.18:
	i32.const	1
	return
.LBB110_19:                             #   in Loop: Header=BB110_3 Depth=1
	end_block                               # label304:
	local.get	3
	i32.const	4
	i32.add 
	local.set	3
	local.get	4
	i64.const	-1
	i64.add 
	local.tee	4
	i64.const	0
	i64.ne  
	br_if   	0                               # 0: up to label303
.LBB110_20:
	end_loop
	end_block                               # label302:
	i32.const	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_map_remove,"",@
	.type	qc_map_remove,@function         # -- Begin function qc_map_remove
qc_map_remove:                          # @qc_map_remove
	.functype	qc_map_remove (i32, i32) -> ()
	.local  	i32, i32, i64, i64, i32, i32, i32, i64
# %bb.0:
	block   	
	block   	
	local.get	0
	i32.load	16
	local.tee	2
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label313
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label313
# %bb.2:
	local.get	0
	i32.load	0
	local.set	3
	local.get	2
	i64.extend_i32_u
	local.set	4
	i64.const	0
	local.set	5
	i32.const	0
	local.set	6
	i32.const	0
	local.set	7
.LBB111_3:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label314:
	block   	
	local.get	3
	local.get	7
	i32.add 
	i32.load	0
	local.tee	8
	i32.eqz
	br_if   	0                               # 0: down to label315
# %bb.4:                                #   in Loop: Header=BB111_3 Depth=1
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	24
	br_table 	{6, 0, 1, 2, 3, 4, 5, 7} # 0: down to label322
                                        # 1: down to label321
                                        # 2: down to label320
                                        # 3: down to label319
                                        # 4: down to label318
                                        # 5: down to label317
                                        # 7: down to label315
.LBB111_5:                              #   in Loop: Header=BB111_3 Depth=1
	end_block                               # label322:
	local.get	8
	f32.load	0
	local.get	1
	f32.load	0
	f32.eq  
	br_if   	9                               # 9: down to label312
	br      	6                               # 6: down to label315
.LBB111_6:                              #   in Loop: Header=BB111_3 Depth=1
	end_block                               # label321:
	local.get	8
	f64.load	0
	local.get	1
	f64.load	0
	f64.eq  
	br_if   	8                               # 8: down to label312
	br      	5                               # 5: down to label315
.LBB111_7:                              #   in Loop: Header=BB111_3 Depth=1
	end_block                               # label320:
	local.get	8
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	br_if   	7                               # 7: down to label312
	br      	4                               # 4: down to label315
.LBB111_8:                              #   in Loop: Header=BB111_3 Depth=1
	end_block                               # label319:
	local.get	8
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	br_if   	6                               # 6: down to label312
	br      	3                               # 3: down to label315
.LBB111_9:                              #   in Loop: Header=BB111_3 Depth=1
	end_block                               # label318:
	local.get	8
	i32.load8_u	0
	local.get	1
	i32.load8_u	0
	i32.eq  
	br_if   	5                               # 5: down to label312
	br      	2                               # 2: down to label315
.LBB111_10:                             #   in Loop: Header=BB111_3 Depth=1
	end_block                               # label317:
	local.get	8
	local.get	1
	call	strcmp
	br_if   	1                               # 1: down to label315
	br      	4                               # 4: down to label312
.LBB111_11:                             #   in Loop: Header=BB111_3 Depth=1
	end_block                               # label316:
	local.get	8
	i32.load	0
	local.get	1
	i32.load	0
	i32.eq  
	br_if   	3                               # 3: down to label312
.LBB111_12:                             #   in Loop: Header=BB111_3 Depth=1
	end_block                               # label315:
	local.get	6
	i32.const	1
	i32.add 
	local.set	6
	local.get	7
	i32.const	4
	i32.add 
	local.set	7
	local.get	4
	local.get	5
	i64.const	1
	i64.add 
	local.tee	5
	i64.ne  
	br_if   	0                               # 0: up to label314
.LBB111_13:
	end_loop
	end_block                               # label313:
	return
.LBB111_14:
	end_block                               # label312:
	block   	
	local.get	2
	i32.const	-1
	i32.add 
	local.tee	8
	local.get	6
	i32.le_s
	br_if   	0                               # 0: down to label323
# %bb.15:
	local.get	5
	local.set	4
	block   	
	local.get	8
	i64.extend_i32_u
	local.tee	9
	local.get	5
	i64.sub 
	i64.const	1
	i64.and 
	i64.eqz
	br_if   	0                               # 0: down to label324
# %bb.16:
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	local.tee	6
	local.get	6
	i32.const	4
	i32.add 
	i32.load	0
	i32.store	0
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	local.tee	7
	local.get	7
	i32.const	4
	i32.add 
	i32.load	0
	i32.store	0
	local.get	5
	i64.const	1
	i64.add 
	local.set	4
.LBB111_17:
	end_block                               # label324:
	local.get	9
	i64.const	-1
	i64.add 
	local.get	5
	i64.eq  
	br_if   	0                               # 0: down to label323
# %bb.18:                               # %.preheader
	local.get	9
	local.get	4
	i64.sub 
	local.set	5
	local.get	4
	i32.wrap_i64
	i32.const	2
	i32.shl 
	local.set	7
.LBB111_19:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label325:
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	local.tee	6
	local.get	6
	i32.const	4
	i32.add 
	i32.load	0
	i32.store	0
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	local.tee	6
	local.get	6
	i32.const	4
	i32.add 
	i32.load	0
	i32.store	0
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	local.tee	6
	i32.const	4
	i32.add 
	local.get	6
	i32.const	8
	i32.add 
	i32.load	0
	i32.store	0
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	local.tee	6
	i32.const	4
	i32.add 
	local.get	6
	i32.const	8
	i32.add 
	i32.load	0
	i32.store	0
	local.get	7
	i32.const	8
	i32.add 
	local.set	7
	local.get	5
	i64.const	-2
	i64.add 
	local.tee	5
	i64.eqz
	i32.eqz
	br_if   	0                               # 0: up to label325
.LBB111_20:
	end_loop
	end_block                               # label323:
	local.get	0
	local.get	8
	i32.store	16
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_print_map,"",@
	.type	qc_print_map,@function          # -- Begin function qc_print_map
qc_print_map:                           # @qc_print_map
	.functype	qc_print_map (i32) -> ()
	.local  	i32, i64, i32, i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	224
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	i32.const	123
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	block   	
	local.get	0
	i32.load	16
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label326
# %bb.1:
	i64.const	0
	local.set	2
	i32.const	0
	local.set	3
.LBB112_2:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label327:
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	24
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label334
                                        # 2: down to label333
                                        # 3: down to label332
                                        # 4: down to label331
                                        # 5: down to label330
                                        # 6: down to label329
                                        # 7: down to label328
.LBB112_3:                              #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label335:
	local.get	1
	local.get	0
	i32.load	0
	local.get	3
	i32.add 
	i32.load	0
	i32.load	0
	i32.store	112
	i32.const	.L.str.34
	local.get	1
	i32.const	112
	i32.add 
	call	printf
	drop
	br      	6                               # 6: down to label328
.LBB112_4:                              #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label334:
	local.get	1
	local.get	0
	i32.load	0
	local.get	3
	i32.add 
	i32.load	0
	f32.load	0
	f64.promote_f32
	f64.store	128
	i32.const	.L.str.35
	local.get	1
	i32.const	128
	i32.add 
	call	printf
	drop
	br      	5                               # 5: down to label328
.LBB112_5:                              #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label333:
	local.get	1
	local.get	0
	i32.load	0
	local.get	3
	i32.add 
	i32.load	0
	f64.load	0
	f64.store	144
	i32.const	.L.str.35
	local.get	1
	i32.const	144
	i32.add 
	call	printf
	drop
	br      	4                               # 4: down to label328
.LBB112_6:                              #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label332:
	local.get	1
	local.get	0
	i32.load	0
	local.get	3
	i32.add 
	i32.load	0
	i32.load8_s	0
	i32.store	160
	i32.const	.L.str.46
	local.get	1
	i32.const	160
	i32.add 
	call	printf
	drop
	br      	3                               # 3: down to label328
.LBB112_7:                              #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label331:
	local.get	1
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.load	0
	local.get	3
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.select
	i32.store	176
	i32.const	.L.str.39
	local.get	1
	i32.const	176
	i32.add 
	call	printf
	drop
	br      	2                               # 2: down to label328
.LBB112_8:                              #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label330:
	i32.const	.L.str.26
	local.set	4
	block   	
	block   	
	block   	
	local.get	0
	i32.load	0
	local.get	3
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.const	3
	i32.and 
	local.tee	5
	br_table 	{2, 1, 0}               # 1: down to label337
                                        # 0: down to label338
.LBB112_9:                              #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label338:
	i32.const	.L.str.28
	i32.const	.L.str.29
	local.get	5
	i32.const	2
	i32.eq  
	i32.select
	local.set	4
	br      	1                               # 1: down to label336
.LBB112_10:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label337:
	i32.const	.L.str.27
	local.set	4
.LBB112_11:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label336:
	local.get	1
	local.get	4
	i32.store	192
	i32.const	.L.str.39
	local.get	1
	i32.const	192
	i32.add 
	call	printf
	drop
	br      	1                               # 1: down to label328
.LBB112_12:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label329:
	local.get	1
	local.get	0
	i32.load	0
	local.get	3
	i32.add 
	i32.load	0
	i32.store	208
	i32.const	.L.str.45
	local.get	1
	i32.const	208
	i32.add 
	call	printf
	drop
.LBB112_13:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label328:
	i32.const	.L.str.49
	i32.const	0
	call	printf
	drop
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	28
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label345
                                        # 2: down to label344
                                        # 3: down to label343
                                        # 4: down to label342
                                        # 5: down to label341
                                        # 6: down to label340
                                        # 7: down to label339
.LBB112_14:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label346:
	local.get	1
	local.get	0
	i32.load	8
	local.get	3
	i32.add 
	i32.load	0
	i32.load	0
	i32.store	0
	i32.const	.L.str.34
	local.get	1
	call	printf
	drop
	br      	6                               # 6: down to label339
.LBB112_15:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label345:
	local.get	1
	local.get	0
	i32.load	8
	local.get	3
	i32.add 
	i32.load	0
	f32.load	0
	f64.promote_f32
	f64.store	16
	i32.const	.L.str.35
	local.get	1
	i32.const	16
	i32.add 
	call	printf
	drop
	br      	5                               # 5: down to label339
.LBB112_16:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label344:
	local.get	1
	local.get	0
	i32.load	8
	local.get	3
	i32.add 
	i32.load	0
	f64.load	0
	f64.store	32
	i32.const	.L.str.35
	local.get	1
	i32.const	32
	i32.add 
	call	printf
	drop
	br      	4                               # 4: down to label339
.LBB112_17:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label343:
	local.get	1
	local.get	0
	i32.load	8
	local.get	3
	i32.add 
	i32.load	0
	i32.load8_s	0
	i32.store	48
	i32.const	.L.str.46
	local.get	1
	i32.const	48
	i32.add 
	call	printf
	drop
	br      	3                               # 3: down to label339
.LBB112_18:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label342:
	local.get	1
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.load	8
	local.get	3
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.select
	i32.store	64
	i32.const	.L.str.39
	local.get	1
	i32.const	64
	i32.add 
	call	printf
	drop
	br      	2                               # 2: down to label339
.LBB112_19:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label341:
	i32.const	.L.str.26
	local.set	4
	block   	
	block   	
	block   	
	local.get	0
	i32.load	8
	local.get	3
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.const	3
	i32.and 
	local.tee	5
	br_table 	{2, 1, 0}               # 1: down to label348
                                        # 0: down to label349
.LBB112_20:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label349:
	i32.const	.L.str.28
	i32.const	.L.str.29
	local.get	5
	i32.const	2
	i32.eq  
	i32.select
	local.set	4
	br      	1                               # 1: down to label347
.LBB112_21:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label348:
	i32.const	.L.str.27
	local.set	4
.LBB112_22:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label347:
	local.get	1
	local.get	4
	i32.store	80
	i32.const	.L.str.39
	local.get	1
	i32.const	80
	i32.add 
	call	printf
	drop
	br      	1                               # 1: down to label339
.LBB112_23:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label340:
	local.get	1
	local.get	0
	i32.load	8
	local.get	3
	i32.add 
	i32.load	0
	i32.store	96
	i32.const	.L.str.45
	local.get	1
	i32.const	96
	i32.add 
	call	printf
	drop
.LBB112_24:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label339:
	block   	
	local.get	2
	local.get	0
	i32.load	16
	local.tee	4
	i32.const	-1
	i32.add 
	i64.extend_i32_s
	i64.ge_s
	br_if   	0                               # 0: down to label350
# %bb.25:                               #   in Loop: Header=BB112_2 Depth=1
	i32.const	.L.str.43
	i32.const	0
	call	printf
	drop
	local.get	0
	i32.load	16
	local.set	4
.LBB112_26:                             #   in Loop: Header=BB112_2 Depth=1
	end_block                               # label350:
	local.get	3
	i32.const	4
	i32.add 
	local.set	3
	local.get	2
	i64.const	1
	i64.add 
	local.tee	2
	local.get	4
	i64.extend_i32_s
	i64.lt_s
	br_if   	0                               # 0: up to label327
.LBB112_27:
	end_loop
	end_block                               # label326:
	i32.const	125
	i32.const	0
	i32.load	stdout
	call	putc
	drop
	local.get	1
	i32.const	224
	i32.add 
	global.set	__stack_pointer
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_map_to_string,"",@
	.type	qc_map_to_string,@function      # -- Begin function qc_map_to_string
qc_map_to_string:                       # @qc_map_to_string
	.functype	qc_map_to_string (i32) -> (i32)
	.local  	i32, i32, i32, i32, i32, i64, i32, i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	352
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	i64.const	256
	call	malloc
	local.tee	2
	i32.const	123
	i32.store8	0
	local.get	2
	i32.const	1
	i32.add 
	local.set	3
	block   	
	local.get	0
	i32.load	16
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label351
# %bb.1:
	i32.const	255
	local.set	4
	i32.const	256
	local.set	5
	i64.const	0
	local.set	6
	i32.const	0
	local.set	7
.LBB113_2:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label352:
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	24
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label359
                                        # 2: down to label358
                                        # 3: down to label357
                                        # 4: down to label356
                                        # 5: down to label355
                                        # 6: down to label354
                                        # 7: down to label353
.LBB113_3:                              #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label360:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.load	0
	i32.store	112
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.34
	local.get	1
	i32.const	112
	i32.add 
	call	snprintf
	drop
	br      	6                               # 6: down to label353
.LBB113_4:                              #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label359:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	f32.load	0
	f64.promote_f32
	f64.store	128
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.35
	local.get	1
	i32.const	128
	i32.add 
	call	snprintf
	drop
	br      	5                               # 5: down to label353
.LBB113_5:                              #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label358:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	f64.load	0
	f64.store	144
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.35
	local.get	1
	i32.const	144
	i32.add 
	call	snprintf
	drop
	br      	4                               # 4: down to label353
.LBB113_6:                              #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label357:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.load8_s	0
	i32.store	160
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.46
	local.get	1
	i32.const	160
	i32.add 
	call	snprintf
	drop
	br      	3                               # 3: down to label353
.LBB113_7:                              #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label356:
	local.get	1
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.select
	i32.store	176
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.39
	local.get	1
	i32.const	176
	i32.add 
	call	snprintf
	drop
	br      	2                               # 2: down to label353
.LBB113_8:                              #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label355:
	i32.const	.L.str.26
	local.set	8
	block   	
	block   	
	block   	
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.const	3
	i32.and 
	local.tee	9
	br_table 	{2, 1, 0}               # 1: down to label362
                                        # 0: down to label363
.LBB113_9:                              #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label363:
	i32.const	.L.str.28
	i32.const	.L.str.29
	local.get	9
	i32.const	2
	i32.eq  
	i32.select
	local.set	8
	br      	1                               # 1: down to label361
.LBB113_10:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label362:
	i32.const	.L.str.27
	local.set	8
.LBB113_11:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label361:
	local.get	1
	local.get	8
	i32.store	192
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.39
	local.get	1
	i32.const	192
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label353
.LBB113_12:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label354:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.store	208
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.45
	local.get	1
	i32.const	208
	i32.add 
	call	snprintf
	drop
.LBB113_13:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label353:
	block   	
	local.get	4
	local.get	1
	i32.const	224
	i32.add 
	call	strlen
	i32.wrap_i64
	local.tee	8
	i32.const	10
	i32.add 
	i32.ge_s
	br_if   	0                               # 0: down to label364
# %bb.14:                               #   in Loop: Header=BB113_2 Depth=1
	local.get	5
	i32.const	1
	i32.shl 
	local.tee	5
	local.get	3
	i64.extend_i32_u
	local.get	2
	i64.extend_i32_u
	i64.sub 
	i32.wrap_i64
	local.tee	3
	i32.sub 
	local.set	4
	local.get	2
	local.get	5
	i64.extend_i32_s
	call	realloc
	local.tee	2
	local.get	3
	i32.add 
	local.set	3
.LBB113_15:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label364:
	local.get	3
	local.get	1
	i32.const	224
	i32.add 
	call	strcpy
	local.get	8
	i32.add 
	local.tee	9
	i32.const	8250
	i32.store16	0:p2align=0
	local.get	4
	local.get	8
	i32.sub 
	i32.const	-2
	i32.add 
	local.set	3
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	28
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label371
                                        # 2: down to label370
                                        # 3: down to label369
                                        # 4: down to label368
                                        # 5: down to label367
                                        # 6: down to label366
                                        # 7: down to label365
.LBB113_16:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label372:
	local.get	1
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	i32.load	0
	i32.load	0
	i32.store	0
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.34
	local.get	1
	call	snprintf
	drop
	br      	6                               # 6: down to label365
.LBB113_17:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label371:
	local.get	1
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	i32.load	0
	f32.load	0
	f64.promote_f32
	f64.store	16
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.35
	local.get	1
	i32.const	16
	i32.add 
	call	snprintf
	drop
	br      	5                               # 5: down to label365
.LBB113_18:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label370:
	local.get	1
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	i32.load	0
	f64.load	0
	f64.store	32
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.35
	local.get	1
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	4                               # 4: down to label365
.LBB113_19:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label369:
	local.get	1
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	i32.load	0
	i32.load8_s	0
	i32.store	48
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.46
	local.get	1
	i32.const	48
	i32.add 
	call	snprintf
	drop
	br      	3                               # 3: down to label365
.LBB113_20:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label368:
	local.get	1
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.select
	i32.store	64
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.39
	local.get	1
	i32.const	64
	i32.add 
	call	snprintf
	drop
	br      	2                               # 2: down to label365
.LBB113_21:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label367:
	i32.const	.L.str.26
	local.set	4
	block   	
	block   	
	block   	
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.const	3
	i32.and 
	local.tee	8
	br_table 	{2, 1, 0}               # 1: down to label374
                                        # 0: down to label375
.LBB113_22:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label375:
	i32.const	.L.str.28
	i32.const	.L.str.29
	local.get	8
	i32.const	2
	i32.eq  
	i32.select
	local.set	4
	br      	1                               # 1: down to label373
.LBB113_23:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label374:
	i32.const	.L.str.27
	local.set	4
.LBB113_24:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label373:
	local.get	1
	local.get	4
	i32.store	80
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.39
	local.get	1
	i32.const	80
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label365
.LBB113_25:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label366:
	local.get	1
	local.get	0
	i32.load	8
	local.get	7
	i32.add 
	i32.load	0
	i32.store	96
	local.get	1
	i32.const	224
	i32.add 
	i64.const	128
	i32.const	.L.str.45
	local.get	1
	i32.const	96
	i32.add 
	call	snprintf
	drop
.LBB113_26:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label365:
	local.get	9
	i32.const	2
	i32.add 
	local.set	8
	block   	
	local.get	3
	local.get	1
	i32.const	224
	i32.add 
	call	strlen
	i32.wrap_i64
	local.tee	9
	i32.const	10
	i32.add 
	i32.ge_s
	br_if   	0                               # 0: down to label376
# %bb.27:                               #   in Loop: Header=BB113_2 Depth=1
	local.get	5
	i32.const	1
	i32.shl 
	local.tee	5
	local.get	8
	i64.extend_i32_u
	local.get	2
	i64.extend_i32_u
	i64.sub 
	i32.wrap_i64
	local.tee	4
	i32.sub 
	local.set	3
	local.get	2
	local.get	5
	i64.extend_i32_s
	call	realloc
	local.tee	2
	local.get	4
	i32.add 
	local.set	8
.LBB113_28:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label376:
	local.get	3
	local.get	9
	i32.sub 
	local.set	4
	local.get	8
	local.get	1
	i32.const	224
	i32.add 
	call	strcpy
	local.get	9
	i32.add 
	local.set	3
	block   	
	local.get	6
	local.get	0
	i32.load	16
	local.tee	8
	i32.const	-1
	i32.add 
	i64.extend_i32_s
	i64.ge_s
	br_if   	0                               # 0: down to label377
# %bb.29:                               #   in Loop: Header=BB113_2 Depth=1
	local.get	3
	i32.const	8236
	i32.store16	0:p2align=0
	local.get	4
	i32.const	-2
	i32.add 
	local.set	4
	local.get	3
	i32.const	2
	i32.add 
	local.set	3
	local.get	0
	i32.load	16
	local.set	8
.LBB113_30:                             #   in Loop: Header=BB113_2 Depth=1
	end_block                               # label377:
	local.get	7
	i32.const	4
	i32.add 
	local.set	7
	local.get	6
	i64.const	1
	i64.add 
	local.tee	6
	local.get	8
	i64.extend_i32_s
	i64.lt_s
	br_if   	0                               # 0: up to label352
.LBB113_31:
	end_loop
	end_block                               # label351:
	local.get	3
	i32.const	125
	i32.store16	0:p2align=0
	local.get	1
	i32.const	352
	i32.add 
	global.set	__stack_pointer
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_map_size,"",@
	.type	qc_map_size,@function           # -- Begin function qc_map_size
qc_map_size:                            # @qc_map_size
	.functype	qc_map_size (i32) -> (i32)
# %bb.0:
	local.get	0
	i32.load	16
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_map_keys,"",@
	.type	qc_map_keys,@function           # -- Begin function qc_map_keys
qc_map_keys:                            # @qc_map_keys
	.functype	qc_map_keys (i32) -> (i32)
	.local  	i32, i32, i32, i32, i64, i64, i32, i64, i32, i32, i32, i64
# %bb.0:
	local.get	0
	i32.load	24
	local.set	1
	i64.const	24
	call	malloc
	local.tee	2
	local.get	1
	i32.store	16
	local.get	2
	i64.const	17179869184
	i64.store	8
	local.get	2
	i64.const	32
	call	malloc
	local.tee	3
	i32.store	0
	block   	
	block   	
	block   	
	local.get	0
	i32.load	16
	local.tee	4
	i32.const	5
	i32.lt_s
	br_if   	0                               # 0: down to label380
# %bb.1:
	local.get	2
	local.get	4
	i32.store	12
	local.get	2
	local.get	3
	local.get	4
	i64.extend_i32_u
	i64.const	3
	i64.shl 
	call	realloc
	local.tee	3
	i32.store	0
	br      	1                               # 1: down to label379
.LBB115_2:
	end_block                               # label380:
	local.get	4
	i32.const	1
	i32.lt_s
	br_if   	1                               # 1: down to label378
.LBB115_3:
	end_block                               # label379:
	block   	
	local.get	1
	i32.const	5
	i32.gt_s
	br_if   	0                               # 0: down to label381
# %bb.4:
	block   	
	block   	
	block   	
	local.get	1
	i32.const	-2
	i32.add 
	br_table 	{1, 0, 0, 0, 2}         # 0: down to label384
                                        # 2: down to label382
.LBB115_5:
	end_block                               # label384:
	local.get	0
	i32.load	0
	local.set	0
	local.get	4
	i64.extend_i32_u
	local.set	5
.LBB115_6:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label385:
	i64.const	1
	call	malloc
	local.tee	1
	local.get	0
	i32.load	0
	i32.load8_u	0
	i32.store8	0
	local.get	3
	local.get	1
	i32.store	0
	local.get	0
	i32.const	4
	i32.add 
	local.set	0
	local.get	3
	i32.const	4
	i32.add 
	local.set	3
	local.get	5
	i64.const	-1
	i64.add 
	local.tee	5
	i64.eqz
	i32.eqz
	br_if   	0                               # 0: up to label385
	br      	4                               # 4: down to label378
.LBB115_7:
	end_loop
	end_block                               # label383:
	local.get	0
	i32.load	0
	local.set	0
	local.get	4
	i64.extend_i32_u
	local.set	5
.LBB115_8:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label386:
	i64.const	8
	call	malloc
	local.set	1
	local.get	0
	i32.load	0
	i64.load	0:p2align=0
	local.set	6
	local.get	3
	local.get	1
	i32.store	0
	local.get	1
	local.get	6
	i64.store	0:p2align=0
	local.get	0
	i32.const	4
	i32.add 
	local.set	0
	local.get	3
	i32.const	4
	i32.add 
	local.set	3
	local.get	5
	i64.const	-1
	i64.add 
	local.tee	5
	i64.eqz
	i32.eqz
	br_if   	0                               # 0: up to label386
	br      	3                               # 3: down to label378
.LBB115_9:
	end_loop
	end_block                               # label382:
	local.get	0
	i32.load	0
	local.set	0
	local.get	4
	i64.extend_i32_u
	local.set	5
.LBB115_10:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label387:
	i64.const	4
	call	malloc
	local.set	1
	local.get	0
	i32.load	0
	i32.load	0:p2align=0
	local.set	7
	local.get	3
	local.get	1
	i32.store	0
	local.get	1
	local.get	7
	i32.store	0:p2align=0
	local.get	0
	i32.const	4
	i32.add 
	local.set	0
	local.get	3
	i32.const	4
	i32.add 
	local.set	3
	local.get	5
	i64.const	-1
	i64.add 
	local.tee	5
	i64.eqz
	i32.eqz
	br_if   	0                               # 0: up to label387
	br      	2                               # 2: down to label378
.LBB115_11:
	end_loop
	end_block                               # label381:
	local.get	0
	i32.load	0
	local.set	0
	local.get	4
	i64.extend_i32_u
	local.set	5
	block   	
	local.get	1
	i32.const	6
	i32.ne  
	br_if   	0                               # 0: down to label388
# %bb.12:
.LBB115_13:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label389:
	local.get	3
	local.get	0
	i32.load	0
	call	strdup
	i32.store	0
	local.get	0
	i32.const	4
	i32.add 
	local.set	0
	local.get	3
	i32.const	4
	i32.add 
	local.set	3
	local.get	5
	i64.const	-1
	i64.add 
	local.tee	5
	i64.const	0
	i64.ne  
	br_if   	0                               # 0: up to label389
	br      	2                               # 2: down to label378
.LBB115_14:
	end_loop
	end_block                               # label388:
	i64.const	0
	local.set	8
	block   	
	local.get	4
	i32.const	6
	i32.lt_u
	br_if   	0                               # 0: down to label390
# %bb.15:
	local.get	3
	i64.extend_i32_u
	local.get	0
	i64.extend_i32_u
	i64.sub 
	i64.const	32
	i64.lt_u
	br_if   	0                               # 0: down to label390
# %bb.16:
	local.get	0
	local.set	1
	local.get	3
	local.set	7
	local.get	5
	i64.const	4294967292
	i64.and 
	local.tee	8
	local.set	6
.LBB115_17:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label391:
	local.get	1
	i32.load	4
	local.set	9
	local.get	7
	i32.const	20
	i32.add 
	local.get	1
	i32.const	20
	i32.add 
	i32.load	0
	i32.store	0
	local.get	1
	i32.load	0
	local.set	10
	local.get	7
	i32.const	16
	i32.add 
	local.tee	11
	local.get	1
	i32.const	16
	i32.add 
	local.tee	1
	i32.load	0
	i32.store	0
	local.get	7
	local.get	9
	i32.store	4
	local.get	7
	local.get	10
	i32.store	0
	local.get	1
	local.set	1
	local.get	11
	local.set	7
	local.get	6
	i64.const	-4
	i64.add 
	local.tee	6
	i64.const	0
	i64.ne  
	br_if   	0                               # 0: up to label391
# %bb.18:
	end_loop
	local.get	8
	local.get	5
	i64.eq  
	br_if   	1                               # 1: down to label378
.LBB115_19:
	end_block                               # label390:
	local.get	8
	local.set	12
	block   	
	local.get	5
	i64.const	3
	i64.and 
	local.tee	6
	i64.eqz
	br_if   	0                               # 0: down to label392
# %bb.20:                               # %.preheader6
	local.get	8
	local.get	6
	i64.add 
	local.set	12
	local.get	0
	local.get	8
	i32.wrap_i64
	i32.const	2
	i32.shl 
	local.tee	7
	i32.add 
	local.set	1
	local.get	3
	local.get	7
	i32.add 
	local.set	7
.LBB115_21:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label393:
	local.get	7
	local.get	1
	i32.load	0
	i32.store	0
	local.get	1
	i32.const	4
	i32.add 
	local.set	1
	local.get	7
	i32.const	4
	i32.add 
	local.set	7
	local.get	6
	i64.const	-1
	i64.add 
	local.tee	6
	i64.const	0
	i64.ne  
	br_if   	0                               # 0: up to label393
.LBB115_22:
	end_loop
	end_block                               # label392:
	local.get	8
	local.get	5
	i64.sub 
	i64.const	-4
	i64.gt_u
	br_if   	0                               # 0: down to label378
# %bb.23:                               # %.preheader4
	local.get	5
	local.get	12
	i64.sub 
	local.set	5
	local.get	12
	i32.wrap_i64
	i32.const	2
	i32.shl 
	local.set	9
.LBB115_24:                             # =>This Inner Loop Header: Depth=1
	loop    	                                # label394:
	local.get	3
	local.get	9
	i32.add 
	local.tee	1
	local.get	0
	local.get	9
	i32.add 
	local.tee	7
	i32.load	0
	i32.store	0
	local.get	1
	i32.const	4
	i32.add 
	local.get	7
	i32.const	4
	i32.add 
	i32.load	0
	i32.store	0
	local.get	1
	i32.const	8
	i32.add 
	local.get	7
	i32.const	8
	i32.add 
	i32.load	0
	i32.store	0
	local.get	1
	i32.const	12
	i32.add 
	local.get	7
	i32.const	12
	i32.add 
	i32.load	0
	i32.store	0
	local.get	0
	i32.const	16
	i32.add 
	local.set	0
	local.get	3
	i32.const	16
	i32.add 
	local.set	3
	local.get	5
	i64.const	-4
	i64.add 
	local.tee	5
	i64.eqz
	i32.eqz
	br_if   	0                               # 0: up to label394
.LBB115_25:
	end_loop
	end_block                               # label378:
	local.get	2
	local.get	4
	i32.store	8
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_list_to_string,"",@
	.type	qc_list_to_string,@function     # -- Begin function qc_list_to_string
qc_list_to_string:                      # @qc_list_to_string
	.functype	qc_list_to_string (i32) -> (i32)
	.local  	i32, i32, i32, i32, i32, i64, i32, i32, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	240
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	i64.const	256
	call	malloc
	local.tee	2
	i32.const	91
	i32.store8	0
	local.get	2
	i32.const	1
	i32.add 
	local.set	3
	block   	
	local.get	0
	i32.load	8
	i32.const	1
	i32.lt_s
	br_if   	0                               # 0: down to label395
# %bb.1:
	i32.const	255
	local.set	4
	i32.const	256
	local.set	5
	i64.const	0
	local.set	6
	i32.const	0
	local.set	7
.LBB116_2:                              # =>This Inner Loop Header: Depth=1
	loop    	                                # label396:
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	block   	
	local.get	0
	i32.load	16
	br_table 	{0, 1, 2, 3, 4, 5, 6, 7} # 1: down to label403
                                        # 2: down to label402
                                        # 3: down to label401
                                        # 4: down to label400
                                        # 5: down to label399
                                        # 6: down to label398
                                        # 7: down to label397
.LBB116_3:                              #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label404:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.load	0
	i32.store	0
	local.get	1
	i32.const	112
	i32.add 
	i64.const	128
	i32.const	.L.str.34
	local.get	1
	call	snprintf
	drop
	br      	6                               # 6: down to label397
.LBB116_4:                              #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label403:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	f32.load	0
	f64.promote_f32
	f64.store	16
	local.get	1
	i32.const	112
	i32.add 
	i64.const	128
	i32.const	.L.str.35
	local.get	1
	i32.const	16
	i32.add 
	call	snprintf
	drop
	br      	5                               # 5: down to label397
.LBB116_5:                              #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label402:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	f64.load	0
	f64.store	32
	local.get	1
	i32.const	112
	i32.add 
	i64.const	128
	i32.const	.L.str.35
	local.get	1
	i32.const	32
	i32.add 
	call	snprintf
	drop
	br      	4                               # 4: down to label397
.LBB116_6:                              #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label401:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.load8_s	0
	i32.store	48
	local.get	1
	i32.const	112
	i32.add 
	i64.const	128
	i32.const	.L.str.46
	local.get	1
	i32.const	48
	i32.add 
	call	snprintf
	drop
	br      	3                               # 3: down to label397
.LBB116_7:                              #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label400:
	local.get	1
	i32.const	.L.str.24
	i32.const	.L.str.25
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.select
	i32.store	64
	local.get	1
	i32.const	112
	i32.add 
	i64.const	128
	i32.const	.L.str.39
	local.get	1
	i32.const	64
	i32.add 
	call	snprintf
	drop
	br      	2                               # 2: down to label397
.LBB116_8:                              #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label399:
	i32.const	.L.str.26
	local.set	8
	block   	
	block   	
	block   	
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.load8_u	0
	i32.const	3
	i32.and 
	local.tee	9
	br_table 	{2, 1, 0}               # 1: down to label406
                                        # 0: down to label407
.LBB116_9:                              #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label407:
	i32.const	.L.str.28
	i32.const	.L.str.29
	local.get	9
	i32.const	2
	i32.eq  
	i32.select
	local.set	8
	br      	1                               # 1: down to label405
.LBB116_10:                             #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label406:
	i32.const	.L.str.27
	local.set	8
.LBB116_11:                             #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label405:
	local.get	1
	local.get	8
	i32.store	80
	local.get	1
	i32.const	112
	i32.add 
	i64.const	128
	i32.const	.L.str.39
	local.get	1
	i32.const	80
	i32.add 
	call	snprintf
	drop
	br      	1                               # 1: down to label397
.LBB116_12:                             #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label398:
	local.get	1
	local.get	0
	i32.load	0
	local.get	7
	i32.add 
	i32.load	0
	i32.store	96
	local.get	1
	i32.const	112
	i32.add 
	i64.const	128
	i32.const	.L.str.45
	local.get	1
	i32.const	96
	i32.add 
	call	snprintf
	drop
.LBB116_13:                             #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label397:
	block   	
	local.get	4
	local.get	1
	i32.const	112
	i32.add 
	call	strlen
	i32.wrap_i64
	local.tee	8
	i32.const	10
	i32.add 
	i32.ge_s
	br_if   	0                               # 0: down to label408
# %bb.14:                               #   in Loop: Header=BB116_2 Depth=1
	local.get	5
	i32.const	1
	i32.shl 
	local.tee	5
	local.get	3
	i64.extend_i32_u
	local.get	2
	i64.extend_i32_u
	i64.sub 
	i32.wrap_i64
	local.tee	3
	i32.sub 
	local.set	4
	local.get	2
	local.get	5
	i64.extend_i32_s
	call	realloc
	local.tee	2
	local.get	3
	i32.add 
	local.set	3
.LBB116_15:                             #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label408:
	local.get	4
	local.get	8
	i32.sub 
	local.set	4
	local.get	3
	local.get	1
	i32.const	112
	i32.add 
	call	strcpy
	local.get	8
	i32.add 
	local.set	3
	block   	
	local.get	6
	local.get	0
	i32.load	8
	local.tee	8
	i32.const	-1
	i32.add 
	i64.extend_i32_s
	i64.ge_s
	br_if   	0                               # 0: down to label409
# %bb.16:                               #   in Loop: Header=BB116_2 Depth=1
	local.get	3
	i32.const	8236
	i32.store16	0:p2align=0
	local.get	4
	i32.const	-2
	i32.add 
	local.set	4
	local.get	3
	i32.const	2
	i32.add 
	local.set	3
	local.get	0
	i32.load	8
	local.set	8
.LBB116_17:                             #   in Loop: Header=BB116_2 Depth=1
	end_block                               # label409:
	local.get	7
	i32.const	4
	i32.add 
	local.set	7
	local.get	6
	i64.const	1
	i64.add 
	local.tee	6
	local.get	8
	i64.extend_i32_s
	i64.lt_s
	br_if   	0                               # 0: up to label396
.LBB116_18:
	end_loop
	end_block                               # label395:
	local.get	3
	i32.const	93
	i32.store16	0:p2align=0
	local.get	1
	i32.const	240
	i32.add 
	global.set	__stack_pointer
	local.get	2
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fopen,"",@
	.type	qc_fopen,@function              # -- Begin function qc_fopen
qc_fopen:                               # @qc_fopen
	.functype	qc_fopen (i32, i32) -> (i32)
# %bb.0:
	local.get	0
	local.get	1
	call	fopen
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fclose,"",@
	.type	qc_fclose,@function             # -- Begin function qc_fclose
qc_fclose:                              # @qc_fclose
	.functype	qc_fclose (i32) -> ()
# %bb.0:
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label410
# %bb.1:
	local.get	0
	call	fclose
	drop
.LBB118_2:
	end_block                               # label410:
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fread,"",@
	.type	qc_fread,@function              # -- Begin function qc_fread
qc_fread:                               # @qc_fread
	.functype	qc_fread (i32) -> (i32)
	.local  	i32, i64, i32
# %bb.0:
	global.get	__stack_pointer
	i32.const	1024
	i32.sub 
	local.tee	1
	global.set	__stack_pointer
	block   	
	block   	
	local.get	0
	br_if   	0                               # 0: down to label412
# %bb.1:
	i32.const	.L.str.2
	call	strdup
	local.set	0
	br      	1                               # 1: down to label411
.LBB119_2:
	end_block                               # label412:
	block   	
	block   	
	local.get	1
	i32.const	1024
	local.get	0
	call	fgets
	br_if   	0                               # 0: down to label414
# %bb.3:
	i32.const	.L.str.2
	local.set	0
	br      	1                               # 1: down to label413
.LBB119_4:
	end_block                               # label414:
	local.get	1
	local.set	0
	local.get	1
	call	strlen
	local.tee	2
	i64.eqz
	br_if   	0                               # 0: down to label413
# %bb.5:
	local.get	2
	i32.wrap_i64
	local.get	1
	i32.add 
	i32.const	-1
	i32.add 
	local.tee	3
	i32.load8_u	0
	i32.const	10
	i32.ne  
	br_if   	0                               # 0: down to label413
# %bb.6:
	local.get	3
	i32.const	0
	i32.store8	0
.LBB119_7:
	end_block                               # label413:
	local.get	0
	call	strdup
	local.set	0
.LBB119_8:
	end_block                               # label411:
	local.get	1
	i32.const	1024
	i32.add 
	global.set	__stack_pointer
	local.get	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_fwrite,"",@
	.type	qc_fwrite,@function             # -- Begin function qc_fwrite
qc_fwrite:                              # @qc_fwrite
	.functype	qc_fwrite (i32, i32) -> ()
# %bb.0:
	block   	
	local.get	0
	i32.eqz
	br_if   	0                               # 0: down to label415
# %bb.1:
	local.get	1
	i32.eqz
	br_if   	0                               # 0: down to label415
# %bb.2:
	local.get	1
	local.get	0
	call	fputs
	drop
	i32.const	10
	local.get	0
	call	fputc
	drop
.LBB120_3:
	end_block                               # label415:
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_variadic_is_empty,"",@
	.type	qc_variadic_is_empty,@function  # -- Begin function qc_variadic_is_empty
qc_variadic_is_empty:                   # @qc_variadic_is_empty
	.functype	qc_variadic_is_empty (i32) -> (i32)
# %bb.0:
	local.get	0
	i32.load	12
	local.get	0
	i32.load	8
	i32.ge_s
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.qc_variadic_next,"",@
	.type	qc_variadic_next,@function      # -- Begin function qc_variadic_next
qc_variadic_next:                       # @qc_variadic_next
	.functype	qc_variadic_next (i32) -> (i32)
	.local  	i32, i32
# %bb.0:
	i32.const	0
	local.set	1
	block   	
	local.get	0
	i32.load	12
	local.tee	2
	local.get	0
	i32.load	8
	i32.ge_s
	br_if   	0                               # 0: down to label416
# %bb.1:
	local.get	0
	local.get	2
	i32.const	1
	i32.add 
	i32.store	12
	local.get	0
	i32.load	0
	local.get	2
	i32.const	2
	i32.shl 
	i32.add 
	i32.load	0
	local.set	1
.LBB122_2:
	end_block                               # label416:
	local.get	1
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.__user_entry,"",@
	.type	__user_entry,@function          # -- Begin function __user_entry
__user_entry:                           # @__user_entry
	.functype	__user_entry () -> (i32)
	.local  	i32, i64
# %bb.0:                                # %entry
	global.get	__stack_pointer
	i32.const	16
	i32.sub 
	local.tee	0
	global.set	__stack_pointer
	local.get	0
	i32.const	0
	i32.store	12
	block   	
	i32.const	0
	br_if   	0                               # 0: down to label417
# %bb.1:                                # %then
	local.get	0
	i64.load32_s	12
	local.set	1
	i32.const	.L__unnamed_1
	call	qc_print_string
	local.get	1
	i32.const	-1
	i32.const	-1
	i32.const	0
	call	qc_fmt_int
	call	qc_print_string
	i32.const	.L__unnamed_2
	call	qc_print_string
.LBB123_2:                              # %ifcont
	end_block                               # label417:
	local.get	0
	i32.const	16
	i32.add 
	global.set	__stack_pointer
	i32.const	0
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.__original_main,"",@
	.globl	__original_main                 # -- Begin function __original_main
	.type	__original_main,@function
__original_main:                        # @__original_main
	.functype	__original_main () -> (i32)
# %bb.0:                                # %entry
	call	__user_entry
                                        # fallthrough-return
	end_function
                                        # -- End function
	.section	.text.main,"",@
	.globl	main                            # -- Begin function main
	.type	main,@function
main:                                   # @main
	.functype	main (i32, i32) -> (i32)
# %bb.0:                                # %body
	call	__original_main
                                        # fallthrough-return
	end_function
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata..L.str,"S",@
.L.str:
	.asciz	"%%%s%d.%dd"
	.size	.L.str, 11

	.type	.L.str.1,@object                # @.str.1
	.section	.rodata..L.str.1,"S",@
.L.str.1:
	.asciz	"0"
	.size	.L.str.1, 2

	.type	.L.str.2,@object                # @.str.2
	.section	.rodata..L.str.2,"S",@
.L.str.2:
	.skip	1
	.size	.L.str.2, 1

	.type	.L.str.3,@object                # @.str.3
	.section	.rodata..L.str.3,"S",@
.L.str.3:
	.asciz	"%%.%dd"
	.size	.L.str.3, 7

	.type	.L.str.4,@object                # @.str.4
	.section	.rodata..L.str.4,"S",@
.L.str.4:
	.asciz	"%%%s%dd"
	.size	.L.str.4, 8

	.type	.L.str.5,@object                # @.str.5
	.section	.rodata..L.str.5,"S",@
.L.str.5:
	.asciz	"%%d"
	.size	.L.str.5, 4

	.type	.L.str.6,@object                # @.str.6
	.section	.rodata..L.str.6,"S",@
.L.str.6:
	.asciz	"%%010lu"
	.size	.L.str.6, 8

	.type	.L.str.7,@object                # @.str.7
	.section	.rodata..L.str.7,"S",@
.L.str.7:
	.asciz	"%%lu"
	.size	.L.str.7, 5

	.type	.L.str.8,@object                # @.str.8
	.section	.rodata..L.str.8,"S",@
.L.str.8:
	.asciz	"%%%s%d.%df"
	.size	.L.str.8, 11

	.type	.L.str.9,@object                # @.str.9
	.section	.rodata..L.str.9,"S",@
.L.str.9:
	.asciz	"%%.%df"
	.size	.L.str.9, 7

	.type	.L.str.10,@object               # @.str.10
	.section	.rodata..L.str.10,"S",@
.L.str.10:
	.asciz	"%%%s%df"
	.size	.L.str.10, 8

	.type	.L.str.11,@object               # @.str.11
	.section	.rodata..L.str.11,"S",@
.L.str.11:
	.asciz	"%%f"
	.size	.L.str.11, 4

	.type	.L.str.12,@object               # @.str.12
	.section	.rodata..L.str.12,"S",@
.L.str.12:
	.asciz	"%%%s%d.%de"
	.size	.L.str.12, 11

	.type	.L.str.13,@object               # @.str.13
	.section	.rodata..L.str.13,"S",@
.L.str.13:
	.asciz	"%%.%de"
	.size	.L.str.13, 7

	.type	.L.str.14,@object               # @.str.14
	.section	.rodata..L.str.14,"S",@
.L.str.14:
	.asciz	"%%%s%de"
	.size	.L.str.14, 8

	.type	.L.str.15,@object               # @.str.15
	.section	.rodata..L.str.15,"S",@
.L.str.15:
	.asciz	"%%e"
	.size	.L.str.15, 4

	.type	.L.str.16,@object               # @.str.16
	.section	.rodata..L.str.16,"S",@
.L.str.16:
	.asciz	"%%%s%dc"
	.size	.L.str.16, 8

	.type	.L.str.17,@object               # @.str.17
	.section	.rodata..L.str.17,"S",@
.L.str.17:
	.asciz	"%%c"
	.size	.L.str.17, 4

	.type	.L.str.18,@object               # @.str.18
	.section	.rodata..L.str.18,"S",@
.L.str.18:
	.asciz	"%%%s%ds"
	.size	.L.str.18, 8

	.type	.L.str.19,@object               # @.str.19
	.section	.rodata..L.str.19,"S",@
.L.str.19:
	.asciz	"%%s"
	.size	.L.str.19, 4

	.type	.L.str.20,@object               # @.str.20
	.section	.rodata..L.str.20,"S",@
.L.str.20:
	.asciz	"%%%s%dx"
	.size	.L.str.20, 8

	.type	.L.str.21,@object               # @.str.21
	.section	.rodata..L.str.21,"S",@
.L.str.21:
	.asciz	"%%x"
	.size	.L.str.21, 4

	.type	.L.str.22,@object               # @.str.22
	.section	.rodata..L.str.22,"S",@
.L.str.22:
	.asciz	"%%%s%do"
	.size	.L.str.22, 8

	.type	.L.str.23,@object               # @.str.23
	.section	.rodata..L.str.23,"S",@
.L.str.23:
	.asciz	"%%o"
	.size	.L.str.23, 4

	.type	.L.str.24,@object               # @.str.24
	.section	.rodata..L.str.24,"S",@
.L.str.24:
	.asciz	"true"
	.size	.L.str.24, 5

	.type	.L.str.25,@object               # @.str.25
	.section	.rodata..L.str.25,"S",@
.L.str.25:
	.asciz	"false"
	.size	.L.str.25, 6

	.type	.L.str.26,@object               # @.str.26
	.section	.rodata..L.str.26,"S",@
.L.str.26:
	.asciz	"none"
	.size	.L.str.26, 5

	.type	.L.str.27,@object               # @.str.27
	.section	.rodata..L.str.27,"S",@
.L.str.27:
	.asciz	"qfalse"
	.size	.L.str.27, 7

	.type	.L.str.28,@object               # @.str.28
	.section	.rodata..L.str.28,"S",@
.L.str.28:
	.asciz	"qtrue"
	.size	.L.str.28, 6

	.type	.L.str.29,@object               # @.str.29
	.section	.rodata..L.str.29,"S",@
.L.str.29:
	.asciz	"both"
	.size	.L.str.29, 5

	.type	.L.str.30,@object               # @.str.30
	.section	.rodata..L.str.30,"S",@
.L.str.30:
	.asciz	"0x%0*jx"
	.size	.L.str.30, 8

	.type	.L.str.31,@object               # @.str.31
	.section	.rodata..L.str.31,"S",@
.L.str.31:
	.asciz	"%*p"
	.size	.L.str.31, 4

	.type	.L.str.32,@object               # @.str.32
	.section	.rodata..L.str.32,"S",@
.L.str.32:
	.asciz	"%p"
	.size	.L.str.32, 3

	.type	.L.str.33,@object               # @.str.33
	.section	.rodata..L.str.33,"S",@
.L.str.33:
	.asciz	"%p\n"
	.size	.L.str.33, 4

	.type	.L.str.34,@object               # @.str.34
	.section	.rodata..L.str.34,"S",@
.L.str.34:
	.asciz	"%d"
	.size	.L.str.34, 3

	.type	.L.str.35,@object               # @.str.35
	.section	.rodata..L.str.35,"S",@
.L.str.35:
	.asciz	"%g"
	.size	.L.str.35, 3

	.type	.L.str.36,@object               # @.str.36
	.section	.rodata..L.str.36,"S",@
.L.str.36:
	.asciz	"%ld"
	.size	.L.str.36, 4

	.type	.L.str.37,@object               # @.str.37
	.section	.rodata..L.str.37,"S",@
.L.str.37:
	.asciz	"%hd"
	.size	.L.str.37, 4

	.type	.L.str.39,@object               # @.str.39
	.section	.rodata..L.str.39,"S",@
.L.str.39:
	.asciz	"%s"
	.size	.L.str.39, 3

	.type	.L.str.43,@object               # @.str.43
	.section	.rodata..L.str.43,"S",@
.L.str.43:
	.asciz	", "
	.size	.L.str.43, 3

	.type	.L.str.45,@object               # @.str.45
	.section	.rodata..L.str.45,"S",@
.L.str.45:
	.asciz	"\"%s\""
	.size	.L.str.45, 5

	.type	.L.str.46,@object               # @.str.46
	.section	.rodata..L.str.46,"S",@
.L.str.46:
	.asciz	"'%c'"
	.size	.L.str.46, 5

	.type	.L.str.47,@object               # @.str.47
	.section	.rodata..L.str.47,"S",@
.L.str.47:
	.asciz	"ERROR"
	.size	.L.str.47, 6

	.type	.L.str.49,@object               # @.str.49
	.section	.rodata..L.str.49,"S",@
.L.str.49:
	.asciz	": "
	.size	.L.str.49, 3

	.type	.Lswitch.table.qc_print_array_qbool,@object # @switch.table.qc_print_array_qbool
	.section	.rodata..Lswitch.table.qc_print_array_qbool,"",@
	.p2align	3, 0x0
.Lswitch.table.qc_print_array_qbool:
	.int32	.L.str.26
	.int32	.L.str.27
	.int32	.L.str.28
	.int32	.L.str.29
	.size	.Lswitch.table.qc_print_array_qbool, 16

	.type	.Lswitch.table.qc_set_leaf_element.52,@object # @switch.table.qc_set_leaf_element.52
	.section	.rodata..Lswitch.table.qc_set_leaf_element.52,"",@
	.p2align	3, 0x0
.Lswitch.table.qc_set_leaf_element.52:
	.int64	8                               # 0x8
	.int64	1                               # 0x1
	.int64	1                               # 0x1
	.int64	1                               # 0x1
	.int64	8                               # 0x8
	.size	.Lswitch.table.qc_set_leaf_element.52, 40

	.type	.Lswitch.table.qc_stringify_jagged_helper,@object # @switch.table.qc_stringify_jagged_helper
	.section	.rodata..Lswitch.table.qc_stringify_jagged_helper,"",@
	.p2align	2, 0x0
.Lswitch.table.qc_stringify_jagged_helper:
	.int32	8                               # 0x8
	.int32	1                               # 0x1
	.int32	1                               # 0x1
	.int32	1                               # 0x1
	.int32	8                               # 0x8
	.size	.Lswitch.table.qc_stringify_jagged_helper, 20

	.type	.Lswitch.table.qc_map_set.54,@object # @switch.table.qc_map_set.54
	.section	.rodata..Lswitch.table.qc_map_set.54,"",@
	.p2align	3, 0x0
.Lswitch.table.qc_map_set.54:
	.int64	8                               # 0x8
	.int64	1                               # 0x1
	.int64	1                               # 0x1
	.int64	1                               # 0x1
	.size	.Lswitch.table.qc_map_set.54, 32

	.type	.L.str.38,@object               # @.str.38
	.section	.rodata..L.str.38,"",@
.L.str.38:
	.asciz	"%i\n"
	.size	.L.str.38, 4

	.type	.L__unnamed_1,@object           # @0
	.section	.rodata..L__unnamed_1,"S",@
.L__unnamed_1:
	.skip	1
	.size	.L__unnamed_1, 1

	.type	.L__unnamed_2,@object           # @1
	.section	.rodata..L__unnamed_2,"",@
.L__unnamed_2:
	.asciz	"\n\000"
	.size	.L__unnamed_2, 3

	.ident	"Debian clang version 21.1.8 (7+b1)"
	.size	stdout, 4
	.size	stderr, 4
	.size	stdin, 4
	.section	.custom_section.producers,"",@
	.int8	1
	.int8	12
	.ascii	"processed-by"
	.int8	1
	.int8	12
	.ascii	"Debian clang"
	.int8	13
	.ascii	"21.1.8 (7+b1)"
	.section	.rodata..L__unnamed_2,"",@
	.section	.custom_section.target_features,"",@
	.int8	8
	.int8	43
	.int8	11
	.ascii	"bulk-memory"
	.int8	43
	.int8	15
	.ascii	"bulk-memory-opt"
	.int8	43
	.int8	22
	.ascii	"call-indirect-overlong"
	.int8	43
	.int8	10
	.ascii	"multivalue"
	.int8	43
	.int8	15
	.ascii	"mutable-globals"
	.int8	43
	.int8	19
	.ascii	"nontrapping-fptoint"
	.int8	43
	.int8	15
	.ascii	"reference-types"
	.int8	43
	.int8	8
	.ascii	"sign-ext"
	.section	.rodata..L__unnamed_2,"",@
