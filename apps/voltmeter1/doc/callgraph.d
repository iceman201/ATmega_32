system_clock_init@system.c: 

system_watchdog_timer_init@system.c: 

system_init@system.c: system_clock_init system_watchdog_timer_init

pio_config_set@pio.c: 

ledmat_init@ledmat.c: pio_config_set pio_config_set

display_clear@display.c: 

display_init@display.c: ledmat_init display_clear

tinygl_text_speed_set@tinygl.c: 

tinygl_clear@tinygl.c: display_clear

tinygl_init@tinygl.c: display_init tinygl_text_speed_set tinygl_clear

tinygl_font_set@tinygl.c: 

tinygl_text_mode_set@tinygl.c: 

tinygl_text_dir_set@tinygl.c: 

display_task_init@voltmeter1.c: tinygl_init tinygl_font_set tinygl_text_mode_set tinygl_text_dir_set

adc_init@adc.c: pio_config_set

adc_enable@adc.c: 

adc_task_init@voltmeter1.c: adc_init adc_enable

timer_init@timer.c: 

timer_get@timer.c: 

timer_wait_until@timer.c: timer_get

task_schedule@task.c: timer_init timer_get timer_wait_until timer_get

tinygl_point@tinygl.c: 

font_pixel_get@font.c: 

tinygl_font_pixel_get@tinygl.c: font_pixel_get

display_pixel_set@display.c: 

tinygl_draw_point@tinygl.c: display_pixel_set

tinygl_draw_char@tinygl.c: tinygl_point tinygl_font_pixel_get tinygl_draw_point tinygl_point tinygl_draw_point tinygl_point tinygl_font_pixel_get tinygl_draw_point tinygl_point tinygl_draw_point

tinygl_draw_string@tinygl.c: tinygl_draw_char

tinygl_text_advance@tinygl.c: tinygl_draw_string tinygl_draw_string

pio_output_high@pio.c: 

pio_output_low@pio.c: 

ledmat_display_column@ledmat.c: pio_output_high pio_output_low pio_output_high pio_output_low

display_update@display.c: ledmat_display_column

tinygl_update@tinygl.c: tinygl_text_advance display_update

display_task@voltmeter1.c: tinygl_update

adc_measure@adc.c: pio_output_high pio_output_low

tinygl_draw_message@tinygl.c: strncpy strlen

tinygl_text@tinygl.c: tinygl_draw_message

adc_task@voltmeter1.c: adc_measure tinygl_text

main@voltmeter1.c: system_init display_task_init adc_task_init task_schedule @display_task @adc_task

