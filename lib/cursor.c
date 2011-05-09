#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <ncurses.h>
#include "display.h"
#include "game.h"
#include "cursor.h"
#include "common.h"

void allocate_cursor(struct cursor **cursor) {
  if (!(*cursor = malloc(sizeof(**cursor)))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
    exit(errno);
  }
}

void initialize_cursor(struct cursor *cursor) {
  cursor->x = CURSOR_BEGIN_X;
  cursor->y = CURSOR_BEGIN_Y;
}

void move_cursor(struct cursor *cursor, enum movement movement) {
  switch (movement) {
  case LEFT:
    if (cursor->x > CURSOR_BEGIN_X) {
      erase_cursor(cursor);
      cursor->x = cursor->x - 8;
      if (cursor->y > CURSOR_BEGIN_Y) {
        move_cursor(cursor, UP);
        move_cursor(cursor, DOWN);
      }
      draw_cursor(cursor);
    }
    break;
  case DOWN:
    if (cursor->y == CURSOR_BEGIN_Y) {
      erase_cursor(cursor);
      switch (cursor->x - 3) {
      case MANEUVRE_0_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre_0);
        break;
      case MANEUVRE_1_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre_1);
        break;
      case MANEUVRE_2_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre_2);
        break;
      case MANEUVRE_3_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre_3);
        break;
      case MANEUVRE_4_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre_4);
        break;
      case MANEUVRE_5_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre_5);
        break;
      case MANEUVRE_6_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre_6);
        break;
      }
      draw_cursor(cursor);
    }
    break;
  case RIGHT:
    if (cursor->x < 49) {
      erase_cursor(cursor);
      cursor->x = cursor->x + 8;
      if (cursor->y > CURSOR_BEGIN_Y) {
        move_cursor(cursor, UP);
        move_cursor(cursor, DOWN);
      }
      draw_cursor(cursor);
    }
    break;
  case UP:
    if (cursor->y > 1) {
      erase_cursor(cursor);
      cursor->y = CURSOR_BEGIN_Y;
      draw_cursor(cursor);
    }
    break;
  }

  /* this is needed because of the screen glitch that moving the cursor
   * on the maneuvre's stacks causes */
  refresh();
  draw_deck(deck);
}
