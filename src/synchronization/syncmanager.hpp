/*
 * gnote
 *
 * Copyright (C) 2012-2014,2017-2021 Aurimas Cernius
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _SYNCHRONIZATION_SYNCMANAGER_HPP_
#define _SYNCHRONIZATION_SYNCMANAGER_HPP_


#include <map>

#include <glibmm/main.h>
#include <glibmm/thread.h>

#include "isyncmanager.hpp"


namespace gnote {

  class IGnote;

namespace sync {

  class SyncServiceAddin;

  class SyncManager
    : public ISyncManager
  {
  public:
    SyncManager(IGnote &, NoteManagerBase &);
    void init();
    virtual void reset_client() override;
    virtual void perform_synchronization(const SyncUI::Ptr & sync_ui) override;
    void synchronization_thread();
    virtual void resolve_conflict(SyncTitleConflictResolution resolution) override;
    virtual bool synchronized_note_xml_matches(const Glib::ustring & noteXml1, const Glib::ustring & noteXml2) override;
    virtual SyncState state() const override
      {
        return m_state;
      }
  protected:
    virtual void initialize_sync_service_addins(NoteManagerBase &);
    virtual void connect_system_signals();
    virtual SyncServiceAddin *get_sync_service_addin(const Glib::ustring & sync_service_id);
    virtual SyncServiceAddin *get_configured_sync_service();
    virtual void delete_notes_in_main_thread(SyncServer & server);
    void delete_notes(SyncServer & server);
    virtual void note_save(const Note::Ptr & note);
    virtual void create_note_in_main_thread(const NoteUpdate & noteUpdate);
    virtual void update_note_in_main_thread(const Note::Ptr & existingNote, const NoteUpdate & noteUpdate);
    virtual void delete_note_in_main_thread(const Note::Ptr & existingNote);
    void create_note(const NoteUpdate & noteUpdate);
    void update_note(const Note::Ptr & existingNote, const NoteUpdate & noteUpdate);
    void delete_note(const Note::Ptr & existingNote);

    std::unique_ptr<SyncClient> m_client;
    SyncUI::Ptr m_sync_ui;
  private:
    void handle_note_saved_or_deleted(const NoteBase::Ptr & note);
    void handle_note_buffer_changed(const NoteBase::Ptr & note);
    void update_sync_action();
    void background_sync_checker();
    void set_state(SyncState new_state);
    void update_local_note(const NoteBase::Ptr & localNote, const NoteUpdate & serverNote, NoteSyncType syncType);
    NoteBase::Ptr find_note_by_uuid(const Glib::ustring & uuid);
    NoteManagerBase & note_mgr();
    void get_synchronized_xml_bits(const Glib::ustring & noteXml, Glib::ustring & title, Glib::ustring & tags, Glib::ustring & content);
    void abort_sync(SyncServer *server);

    IGnote & m_gnote;
    NoteManagerBase & m_note_manager;
    SyncState m_state;
    Glib::Thread *m_sync_thread;
    SyncTitleConflictResolution m_conflict_resolution;
    utils::InterruptableTimeout m_autosync_timer;
    int m_autosync_timeout_pref_minutes;
    int m_current_autosync_timeout_minutes;
    Glib::DateTime m_last_background_check;
  };


}
}

#endif
