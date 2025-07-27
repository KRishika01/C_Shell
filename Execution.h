#ifndef EXECUTION_H
#define EXECUTION_H

#include "display.h"
#include "input.h"
#include "log.h"
#include "reveal.h"
#include "hop.h"
#include "proclore.h"
#include "seek.h"
#include "bg_fg.h"
#include "activities.h"
#include "symbols.h"
#include "pipes.h"
#include "fg_bg_b.h"
#include "pipes_symbols.h"
#include "ping.h"
#include "man.h"

void commands_execution(char *input);
void alias_execution(char *input);

#endif