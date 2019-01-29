PROG=proj

SRCS = proj.c keyboard.c ps2Mouse.c timer.c vbe.c video_graphics.c controlSprite.c board.c xpm.c video_settings.c rtc.c mouse.c menu.c interrupt_handling.c event_handlers.c	serial_port.c clock.c

CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>

