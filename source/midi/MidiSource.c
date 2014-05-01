//
// MidiSource.c - MrsWatson
// Created by Nik Reiman on 1/5/12.
// Copyright (c) 2012 Teragon Audio. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base/FileUtilities.h"
#include "logging/EventLogger.h"
#include "midi/MidiSourceFile.h"

MidiSourceType guessMidiSourceType(const CharString midiSourceTypeString) {
  if(!charStringIsEmpty(midiSourceTypeString)) {
    const char* fileExtension = getFileExtension(midiSourceTypeString->data);
    if(fileExtension == NULL) {
      return MIDI_SOURCE_TYPE_INVALID;
    }
    else if(!strcasecmp(fileExtension, "mid") || !strcasecmp(fileExtension, "midi")) {
      return MIDI_SOURCE_TYPE_FILE;
    }
    else {
      logCritical("MIDI source '%s' does not match any supported type");
      return MIDI_SOURCE_TYPE_INVALID;
    }
  }
  else {
    logInternalError("MIDI source type was null");
    return MIDI_SOURCE_TYPE_INVALID;
  }
}

MidiSource newMidiSource(MidiSourceType midiSourceType, const CharString midiSourceName) {
  switch(midiSourceType) {
    case MIDI_SOURCE_TYPE_FILE:
      return newMidiSourceFile(midiSourceName);
    default:
      return NULL;
  }
}

void freeMidiSource(MidiSource self) {
  self->freeMidiSourceData(self->extraData);
  freeCharString(self->sourceName);
  free(self);
}
