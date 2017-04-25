#include "torrent_handle.h"

using namespace v8;

Nan::Persistent<Function> TorrentHandle::constructor;

NAN_MODULE_INIT(TorrentHandle::Init) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(NewInstance);
  tpl->SetClassName(Nan::New("TorrentHandle").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "getPeerInfo", get_peer_info);
  Nan::SetPrototypeMethod(tpl, "status", status);
  Nan::SetPrototypeMethod(tpl, "getDownloadQueue", get_download_queue);
  Nan::SetPrototypeMethod(tpl, "fileProgress", file_progress);
  //Nan::SetPrototypeMethod(tpl, "trackers", trackers);
  //Nan::SetPrototypeMethod(tpl, "replaceTrackers", replace_trackers);
  //Nan::SetPrototypeMethod(tpl, "addTracker", add_tracker);
  Nan::SetPrototypeMethod(tpl, "addUrlSeed", add_url_seed);
  Nan::SetPrototypeMethod(tpl, "removeUrlSeed", remove_url_seed);
  Nan::SetPrototypeMethod(tpl, "urlSeeds", url_seeds);
  Nan::SetPrototypeMethod(tpl, "addHttpSeed", add_http_seed);
   Nan::SetPrototypeMethod(tpl, "removeHttpSeed", remove_http_seed);
   Nan::SetPrototypeMethod(tpl, "httpSeeds", http_seeds);
   Nan::SetPrototypeMethod(tpl, "setMetadata", set_metadata);
   Nan::SetPrototypeMethod(tpl, "isValid", is_valid);
   //Nan::SetPrototypeMethod(tpl, "has_metadata", has_metadata);
   Nan::SetPrototypeMethod(tpl, "pause", pause);
   Nan::SetPrototypeMethod(tpl, "resume", resume);
   Nan::SetPrototypeMethod(tpl, "clearError", clear_error);
   Nan::SetPrototypeMethod(tpl, "setPriority", set_priority);
   Nan::SetPrototypeMethod(tpl, "superSeeding", super_seeding);

   Nan::SetPrototypeMethod(tpl, "autoManaged", auto_managed);
   Nan::SetPrototypeMethod(tpl, "queuePosition", queue_position);
   Nan::SetPrototypeMethod(tpl, "queuePositionUp", queue_position_up);
   Nan::SetPrototypeMethod(tpl, "queuePositionDown", queue_position_down);
   Nan::SetPrototypeMethod(tpl, "queuePositionTop", queue_position_top);
   Nan::SetPrototypeMethod(tpl, "queuePositionBottom", queue_position_bottom);

/*#ifndef TORRENT_DISABLE_RESOLVE_COUNTRIES
   Nan::SetPrototypeMethod(tpl, "resolve_countries", resolve_countries);
#endif*/

   Nan::SetPrototypeMethod(tpl, "addPiece", add_piece);
   Nan::SetPrototypeMethod(tpl, "readPiece", read_piece);
   Nan::SetPrototypeMethod(tpl, "havePiece", have_piece);
   Nan::SetPrototypeMethod(tpl, "setPieceDeadline", set_piece_deadline);
   Nan::SetPrototypeMethod(tpl, "resetPieceDeadline", reset_piece_deadline);
   Nan::SetPrototypeMethod(tpl, "pieceAvailability", piece_availability);
   Nan::SetPrototypeMethod(tpl, "piecePriority", piece_priority);
   Nan::SetPrototypeMethod(tpl, "prioritizePieces", prioritize_pieces);
   Nan::SetPrototypeMethod(tpl, "piecePriorities", piece_priorities);
   Nan::SetPrototypeMethod(tpl, "prioritizeFiles", prioritize_files);
   Nan::SetPrototypeMethod(tpl, "filePriorities", file_priorities);
   Nan::SetPrototypeMethod(tpl, "filePriority", file_priority);
#ifndef TORRENT_NO_DEPRECATE
   Nan::SetPrototypeMethod(tpl, "useInterface", use_interface);
#endif
   Nan::SetPrototypeMethod(tpl, "saveResume_data", save_resume_data);
   Nan::SetPrototypeMethod(tpl, "needSaveResumeData", need_save_resume_data);
   Nan::SetPrototypeMethod(tpl, "forceReannounce", force_reannounce);

#ifndef TORRENT_DISABLE_DHT
   Nan::SetPrototypeMethod(tpl, "forceDhtAnnounce", force_dht_announce);
#endif

   Nan::SetPrototypeMethod(tpl, "scrapeTracker", scrape_tracker);
   Nan::SetPrototypeMethod(tpl, "setUploadMode", set_upload_mode);
   Nan::SetPrototypeMethod(tpl, "setShareMode", set_share_mode);
   Nan::SetPrototypeMethod(tpl, "flushCache", flush_cache);
   Nan::SetPrototypeMethod(tpl, "applyIpFilter", apply_ip_filter);
   Nan::SetPrototypeMethod(tpl, "setUploadLimit", set_upload_limit);
   Nan::SetPrototypeMethod(tpl, "setDownloadLimit", set_download_limit);
   Nan::SetPrototypeMethod(tpl, "uploadLimit", upload_limit);
   Nan::SetPrototypeMethod(tpl, "downloadLimit", download_limit);
   Nan::SetPrototypeMethod(tpl, "setSequentialDownload", set_sequential_download);
   Nan::SetPrototypeMethod(tpl, "connectPeer", connect_peer);
   Nan::SetPrototypeMethod(tpl, "savePath", save_path);
   //Nan::SetPrototypeMethod(tpl, "make_magnet_link", make_magnet_link);
   Nan::SetPrototypeMethod(tpl, "setMaxUploads", set_max_uploads);
   Nan::SetPrototypeMethod(tpl, "maxUploads", max_uploads);
   Nan::SetPrototypeMethod(tpl, "setMaxConnections", set_max_connections);
   Nan::SetPrototypeMethod(tpl, "maxConnections", max_connections);
   //Nan::SetPrototypeMethod(tpl, "set_tracker_login", set_tracker_login);
   Nan::SetPrototypeMethod(tpl, "moveStorage", move_storage);
   Nan::SetPrototypeMethod(tpl, "infoHash", info_hash);
   Nan::SetPrototypeMethod(tpl, "forceRecheck", force_recheck);
   Nan::SetPrototypeMethod(tpl, "renameFile", rename_file);
   Nan::SetPrototypeMethod(tpl, "setSSLCertificate", set_ssl_certificate);

   Nan::SetPrototypeMethod(tpl, "torrentFile", torrent_file);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("TorrentHandle").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

Local<Object> TorrentHandle::New(libtorrent::torrent_handle th) {
    Nan::EscapableHandleScope scope;

    Local<Function> cons = Nan::New(constructor);
    Nan::MaybeLocal<Object> obj = cons->NewInstance(Nan::GetCurrentContext());

    Nan::ObjectWrap::Unwrap<TorrentHandle>(obj.ToLocalChecked())->th_ = th;

    return scope.Escape(obj.ToLocalChecked());
}

NAN_METHOD(TorrentHandle::NewInstance) {
  if (!info.IsConstructCall()) {
    Nan::ThrowTypeError("Use the new operator to create instances of this object.");
    return;
  }

  TorrentHandle* obj = new TorrentHandle();
  obj->Wrap(info.This());

  RETURN(info.This());
};

NAN_METHOD(TorrentHandle::get_peer_info) {
    std::vector<libtorrent::peer_info> res;

    // Get error exception here ?
    TorrentHandle::Unwrap(info.This())->get_peer_info(res);

    Local<Array> ret = Nan::New<Array>();

    for(libtorrent::peer_info i : res)
      ret->Set(ret->Length(), libtorrent::node::peer_info::encode(i));

    RETURN(ret);
};


NAN_METHOD(TorrentHandle::status) {
    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());
    libtorrent::torrent_status st;

    if (info.Length() == 1)
        st = th->status(info[0]->IntegerValue());
    else
        st = th->status();

    RETURN(libtorrent::node::torrent_status::encode(st));
}

NAN_METHOD(TorrentHandle::get_download_queue) {
    std::vector<libtorrent::partial_piece_info> res;
    TorrentHandle::Unwrap(info.This())->get_download_queue(res);

    Local<Array> ret = Nan::New<Array>();

    for (std::vector<libtorrent::partial_piece_info>::iterator i(res.begin()), e(res.end()); i != e; ++i) {
        Local<Object> obj = Nan::New<Object>();

        obj->Set(Nan::New("piece_index").ToLocalChecked(), Nan::New<Integer>(i->piece_index));
        obj->Set(Nan::New("blocks_in_piece").ToLocalChecked(), Nan::New<Integer>(i->blocks_in_piece));
        obj->Set(Nan::New("finished").ToLocalChecked(), Nan::New<Integer>(i->piece_index));
        obj->Set(Nan::New("writing").ToLocalChecked(), Nan::New<Integer>(i->piece_index));
        obj->Set(Nan::New("requested").ToLocalChecked(), Nan::New<Integer>(i->piece_index));

        Local<Array> blocks = Nan::New<Array>();

        for (int k = 0; k < i->blocks_in_piece; ++k) {
            Local<Object> block = Nan::New<Object>();
            Local<Array> peer = Nan::New<Array>();

            block->Set(Nan::New("state").ToLocalChecked(), Nan::New<Uint32>(i->blocks[k].state));
            block->Set(Nan::New("num_peers").ToLocalChecked(), Nan::New<Uint32>(i->blocks[k].num_peers));
            block->Set(Nan::New("bytes_progress").ToLocalChecked(), Nan::New<Uint32>(i->blocks[k].bytes_progress));
            block->Set(Nan::New("block_size").ToLocalChecked(), Nan::New<Uint32>(i->blocks[k].block_size));

            peer->Set(0, Nan::New<String>(i->blocks[k].peer().address().to_string()).ToLocalChecked());
            peer->Set(1, Nan::New<Integer>(i->blocks[k].peer().port()));

            block->Set(Nan::New("peer").ToLocalChecked(), peer);
            blocks->Set(blocks->Length(), block);
        }

        obj->Set(Nan::New("blocks").ToLocalChecked(), blocks);
        ret->Set(ret->Length(), obj);
    }

    RETURN(ret);
};

NAN_METHOD(TorrentHandle::file_progress) {
    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());
    std::vector<std::int64_t> res;

    res.reserve(th->torrent_file()->num_files());

    v8::Local<v8::Array> ret = Nan::New<v8::Array>();

    // Only calculate file progress at piece granularity. Cheaper.
    th->file_progress(res, libtorrent::torrent_handle::piece_granularity);

    for (std::vector<std::int64_t>::iterator i(res.begin()), e(res.end()); i != e; ++i) {
      ret->Set(ret->Length(), Nan::New<v8::Number>(*i));
    }

    RETURN(ret);
}

/*NAN_METHOD(TorrentHandle::trackers) {
    std::vector<libtorrent::announce_entry> const res = TorrentHandle::Unwrap(info.This())->trackers();

    Local<Array> ret = Nan::New<Array>();

    for (std::vector<libtorrent::announce_entry>::const_iterator i(res.begin()), e(res.end()); i != e; ++i)
        ret->Set(ret->Length(), announce_entry_to_object(*i));

    info.GetReturnValue().Set(ret);
}*/

/*NAN_METHOD(TorrentHandle::replace_trackers) {
    Nan::HandleScope scope;

    std::vector<libtorrent::announce_entry> trackers;

    Local<Array> src = info[0].As<Array>();

    for (uint32_t i = 0, e = src->Length(); i < e; ++i)
        trackers.push_back(announce_entry_from_object(src->Get(i)->ToObject()));

    TorrentHandle::Unwrap(info.This())->replace_trackers(trackers);

    info.GetReturnValue().SetUndefined();
}*/

/*NAN_METHOD(TorrentHandle::add_tracker) {
    Nan::HandleScope scope;

    TorrentHandle::Unwrap(info.This())->add_tracker(announce_entry_from_object(info[0]->ToObject()));

    info.GetReturnValue().SetUndefined();
}*/

NAN_METHOD(TorrentHandle::add_url_seed) {

    TorrentHandle::Unwrap(info.This())->add_url_seed(std::string(*Nan::Utf8String(info[0])));

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::remove_url_seed) {

    TorrentHandle::Unwrap(info.This())->remove_url_seed(std::string(*Nan::Utf8String(info[0])));
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::url_seeds) {
    std::set<std::string> urls = TorrentHandle::Unwrap(info.This())->url_seeds();

    Local<Array> ret = Nan::New<Array>();

    for (std::set<std::string>::iterator i(urls.begin()), e(urls.end()); i != e; ++i)
        ret->Set(ret->Length(), Nan::New<String>(*i).ToLocalChecked());

    RETURN(ret);
};

NAN_METHOD(TorrentHandle::add_http_seed) {

    TorrentHandle::Unwrap(info.This())->add_http_seed(std::string(*Nan::Utf8String(info[0])));

    info.GetReturnValue().SetUndefined();
}

NAN_METHOD(TorrentHandle::remove_http_seed) {

    TorrentHandle::Unwrap(info.This())->remove_http_seed(std::string(*Nan::Utf8String(info[0])));
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::http_seeds) {

    std::set<std::string> urls = TorrentHandle::Unwrap(info.This())->http_seeds();

    Local<Array> ret = Nan::New<Array>();

    for (std::set<std::string>::iterator i(urls.begin()), e(urls.end()); i != e; ++i)
        ret->Set(ret->Length(), Nan::New<String>((*i).c_str()).ToLocalChecked());

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::set_metadata) {
    std::string md(*Nan::Utf8String(info[0]));

    TorrentHandle::Unwrap(info.This())->set_metadata(md.c_str(), md.size());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::is_valid) {

    info.GetReturnValue().Set(Nan::New<Boolean>(TorrentHandle::Unwrap(info.This())->is_valid()));
};

/*NAN_METHOD(TorrentHandle::has_metadata) {
    Nan::HandleScope scope;

    info.GetReturnValue().Set(Nan::New<Boolean>(TorrentHandle::Unwrap(info.This())->has_metadata()));
};*/

NAN_METHOD(TorrentHandle::pause) {

    if (info.Length() == 1)
        TorrentHandle::Unwrap(info.This())->pause(info[0]->IntegerValue());
    else
        TorrentHandle::Unwrap(info.This())->pause();

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::resume) {

    TorrentHandle::Unwrap(info.This())->resume();
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::clear_error) {

    TorrentHandle::Unwrap(info.This())->clear_error();
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::set_priority) {

    TorrentHandle::Unwrap(info.This())->set_priority(info[0]->IntegerValue());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::super_seeding) {

    TorrentHandle::Unwrap(info.This())->super_seeding(info[0]->BooleanValue());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::auto_managed) {

    TorrentHandle::Unwrap(info.This())->auto_managed(info[0]->BooleanValue());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::queue_position) {
    RETURN(Nan::New<Integer>(TorrentHandle::Unwrap(info.This())->queue_position()));
};

NAN_METHOD(TorrentHandle::queue_position_up) {

    TorrentHandle::Unwrap(info.This())->queue_position_up();
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::queue_position_down) {

    TorrentHandle::Unwrap(info.This())->queue_position_down();
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::queue_position_top) {

    TorrentHandle::Unwrap(info.This())->queue_position_top();
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::queue_position_bottom) {

    TorrentHandle::Unwrap(info.This())->queue_position_bottom();
    RETURN_VOID;
};

/*#ifndef TORRENT_DISABLE_RESOLVE_COUNTRIES
NAN_METHOD(TorrentHandle::resolve_countries) {
    Nan::HandleScope scope;

    if (info.Length() == 1) {
        TorrentHandle::Unwrap(info.This())->resolve_countries(info[0]->BooleanValue());
        info.GetReturnValue().SetUndefined();
    } else {
        info.GetReturnValue().Set(Nan::New<Boolean>(TorrentHandle::Unwrap(info.This())->resolve_countries()));
    }
}
#endif*/

NAN_METHOD(TorrentHandle::add_piece) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());

    std::string data(*Nan::Utf8String(info[1]));

    if (info.Length() == 3)
        th->add_piece(info[0]->IntegerValue(), data.c_str(), info[2]->IntegerValue());
    else
        th->add_piece(info[0]->IntegerValue(), data.c_str());

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::read_piece) {

    TorrentHandle::Unwrap(info.This())->read_piece(info[0]->IntegerValue());

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::have_piece) {

    bool ret = TorrentHandle::Unwrap(info.This())->have_piece(info[0]->IntegerValue());

    RETURN(Nan::New<Boolean>(ret));
};

NAN_METHOD(TorrentHandle::set_piece_deadline) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());

    int index = info[0]->IntegerValue(), deadline = info[1]->IntegerValue();

    if (info.Length() == 3)
        th->set_piece_deadline(index, deadline, info[2]->IntegerValue());
    else
        th->set_piece_deadline(index, deadline);
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::reset_piece_deadline) {

    TorrentHandle::Unwrap(info.This())->reset_piece_deadline(info[0]->IntegerValue());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::piece_availability) {

    std::vector<int> a;

    Local<Array> avail = info[0].As<Array>();

    for (uint32_t i(0), e(avail->Length()); i < e; ++i)
        a.push_back(avail->Get(i)->IntegerValue());

    TorrentHandle::Unwrap(info.This())->piece_availability(a);

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::piece_priority) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());

    if (info.Length() == 2) {
        th->piece_priority(info[0]->IntegerValue(), info[1]->IntegerValue());
        RETURN_VOID;
    } else {
        RETURN(Nan::New<Integer>(th->piece_priority(info[0]->IntegerValue())));
    }
}

NAN_METHOD(TorrentHandle::prioritize_pieces) {

    std::vector<int> p;

    Local<Array> pieces = info[0].As<Array>();

    for (uint32_t i(0), e(pieces->Length()); i < e; ++i)
        p.push_back(pieces->Get(i)->IntegerValue());

    TorrentHandle::Unwrap(info.This())->prioritize_pieces(p);

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::piece_priorities) {

    std::vector<int> p(TorrentHandle::Unwrap(info.This())->piece_priorities());

    Local<Array> ret = Nan::New<Array>();

    for (std::vector<int>::iterator i(p.begin()), e(p.end()); i != e; ++i)
        ret->Set(ret->Length(), Nan::New<Integer>(*i));

    RETURN(ret);
};

NAN_METHOD(TorrentHandle::prioritize_files) {

    std::vector<int> f;

    Local<Array> files = info[0].As<Array>();

    for (uint32_t i(0), e(files->Length()); i < e; ++i)
        f.push_back(files->Get(i)->IntegerValue());

    TorrentHandle::Unwrap(info.This())->prioritize_files(f);

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::file_priorities) {

    std::vector<int> f(TorrentHandle::Unwrap(info.This())->file_priorities());

    Local<Array> ret = Nan::New<Array>();

    for (std::vector<int>::iterator i(f.begin()), e(f.end()); i != e; ++i)
        ret->Set(ret->Length(), Nan::New<Integer>(*i));

    RETURN(ret);
};

NAN_METHOD(TorrentHandle::file_priority) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());

    if (info.Length() == 2) {
        th->file_priority(info[0]->IntegerValue(), info[1]->IntegerValue());
        info.GetReturnValue().SetUndefined();
    } else {
        info.GetReturnValue().Set(Nan::New<Integer>(th->file_priority(info[0]->IntegerValue())));
    }

    RETURN_VOID;
};

#ifndef TORRENT_NO_DEPRECATE
NAN_METHOD(TorrentHandle::use_interface) {

    TorrentHandle::Unwrap(info.This())->use_interface(*Nan::Utf8String(info[0]));

    RETURN_VOID;
};
#endif

NAN_METHOD(TorrentHandle::save_resume_data) {

    if (info.Length() == 1)
        TorrentHandle::Unwrap(info.This())->save_resume_data(info[0]->IntegerValue());
    else
        TorrentHandle::Unwrap(info.This())->save_resume_data();

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::need_save_resume_data) {

    RETURN(Nan::New<Boolean>(TorrentHandle::Unwrap(info.This())->need_save_resume_data()));
};

NAN_METHOD(TorrentHandle::force_reannounce) {

    TorrentHandle::Unwrap(info.This())->force_reannounce();

    RETURN_VOID;
};

#ifndef TORRENT_DISABLE_DHT
NAN_METHOD(TorrentHandle::force_dht_announce) {

    TorrentHandle::Unwrap(info.This())->force_dht_announce();
    RETURN_VOID;
};

#endif

NAN_METHOD(TorrentHandle::scrape_tracker) {

    TorrentHandle::Unwrap(info.This())->scrape_tracker();
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::set_upload_mode) {
    TorrentHandle::Unwrap(info.This())->set_upload_mode(info[0]->BooleanValue());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::set_share_mode) {

    TorrentHandle::Unwrap(info.This())->set_share_mode(info[0]->BooleanValue());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::flush_cache) {

    TorrentHandle::Unwrap(info.This())->flush_cache();
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::apply_ip_filter) {

    TorrentHandle::Unwrap(info.This())->apply_ip_filter(info[0]->BooleanValue());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::set_upload_limit) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());

    th->set_upload_limit(info[0]->Int32Value());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::set_download_limit) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());

    th->set_download_limit(info[0]->Int32Value());

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::upload_limit) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());
    RETURN(Nan::New<Int32>(th->upload_limit()));
};

NAN_METHOD(TorrentHandle::download_limit) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());
    RETURN(Nan::New<Int32>(th->download_limit()));
};

NAN_METHOD(TorrentHandle::set_sequential_download) {

    TorrentHandle::Unwrap(info.This())->set_sequential_download(info[0]->BooleanValue());
    RETURN_VOID;
};

/*NAN_METHOD(TorrentHandle::make_magnet_link) {
    Nan::HandleScope scope;

    libtorrent::torrent_handle *handle = TorrentHandle::Unwrap(info.This());
    std::string ret;

    if (!handle->is_valid()) {
        ret = "";
    } else {
        libtorrent::sha1_hash const& ih = handle->info_hash();
        ret += "magnet:?xt=urn:btih:";
        ret += libtorrent::to_hex(ih.to_string());

        libtorrent::torrent_status st = handle->status(libtorrent::torrent_handle::query_name);
        if (!st.name.empty())
        {
                ret += "&dn=";
                ret += libtorrent::escape_string(st.name.c_str(), st.name.length());
        }

        std::vector<libtorrent::announce_entry> const& tr = handle->trackers();
        for (std::vector<libtorrent::announce_entry>::const_iterator i = tr.begin(), end(tr.end()); i != end; ++i)
        {
                ret += "&tr=";
                ret +=libtorrent::escape_string(i->url.c_str(), i->url.length());
        }

        std::set<std::string> seeds = handle->url_seeds();
        for (std::set<std::string>::iterator i = seeds.begin()
                , end(seeds.end()); i != end; ++i)
        {
                ret += "&ws=";
                ret += libtorrent::escape_string(i->c_str(), i->length());
        }
    }

    info.GetReturnValue().Set(Nan::New<String>(ret).ToLocalChecked());
}*/

NAN_METHOD(TorrentHandle::connect_peer) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());

    libtorrent::tcp::endpoint ep = libtorrent::node::endpoint::decode(info[0]);

    th->connect_peer(ep);

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::save_path) {
    auto handle = TorrentHandle::Unwrap(info.This());
    libtorrent::torrent_status st = handle->status(libtorrent::torrent_handle::query_save_path);
    info.GetReturnValue().Set(Nan::New<String>(st.save_path).ToLocalChecked());
};

NAN_METHOD(TorrentHandle::set_max_uploads) {

    TorrentHandle::Unwrap(info.This())->set_max_uploads(info[0]->IntegerValue());

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::max_uploads) {
    RETURN(Nan::New<Integer>(TorrentHandle::Unwrap(info.This())->max_uploads()));
};

NAN_METHOD(TorrentHandle::set_max_connections) {

    TorrentHandle::Unwrap(info.This())->set_max_connections(info[0]->IntegerValue());
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::max_connections) {

    RETURN(Nan::New<Integer>(TorrentHandle::Unwrap(info.This())->max_connections()));
};

/*NAN_METHOD(TorrentHandle::set_tracker_login) {
    Nan::HandleScope scope;

    TorrentHandle::Unwrap(info.This())->set_tracker_login(std::string(*Nan::Utf8String(info[0])),
        std::string(*Nan::Utf8String(info[1])));

    info.GetReturnValue().SetUndefined();
}*/

NAN_METHOD(TorrentHandle::move_storage) {

    TorrentHandle::Unwrap(info.This())->move_storage(std::string(*Nan::Utf8String(info[0])));

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::info_hash) {

    libtorrent::sha1_hash h(TorrentHandle::Unwrap(info.This())->info_hash());

    RETURN(libtorrent::node::sha1_hash::encode(h));
};

NAN_METHOD(TorrentHandle::force_recheck) {

    TorrentHandle::Unwrap(info.This())->force_recheck();

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::rename_file) {

    TorrentHandle::Unwrap(info.This())->rename_file(info[0]->IntegerValue(),
        std::string(*Nan::Utf8String(info[1])));

    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::set_ssl_certificate) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());

    std::string certificate(*Nan::Utf8String(info[0])),
        private_key(*Nan::Utf8String(info[1])),
        dh_params(*Nan::Utf8String(info[2]));

    if (info.Length() == 4)
        th->set_ssl_certificate(certificate, private_key, dh_params, std::string(*Nan::Utf8String(info[3])));
    else
        th->set_ssl_certificate(certificate, private_key, dh_params);
    RETURN_VOID;
};

NAN_METHOD(TorrentHandle::torrent_file) {

    libtorrent::torrent_handle* th = TorrentHandle::Unwrap(info.This());

    // Not good...
    boost::shared_ptr<const libtorrent::torrent_info> torrent_info = th->torrent_file();

    if (torrent_info.get()) {
      RETURN(TorrentInfo::New(torrent_info));
    } else {
      RETURN_VOID;
    }
}
