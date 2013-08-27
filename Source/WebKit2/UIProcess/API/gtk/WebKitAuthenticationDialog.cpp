/*
 * Copyright (C) 2012 Igalia S.L.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "WebKitAuthenticationDialog.h"

#include "AuthenticationDecisionListener.h"
#include "WebKitAuthenticationRequestPrivate.h"
#include "WebKitCredentialPrivate.h"
#include "WebKitPrivate.h"
#include "WebKitWebView.h"

using namespace WebKit;

struct _WebKitAuthenticationDialogPrivate {
    GRefPtr<WebKitAuthenticationRequest> request;
    GtkWidget* authWidget;
    GtkWidget* defaultButton;
    unsigned long loadFailedEventID;
    GRefPtr<GtkStyleContext> styleContext;
    WebKitWebView* webView;
};

WEBKIT_DEFINE_TYPE(WebKitAuthenticationDialog, webkit_authentication_dialog, GTK_TYPE_EVENT_BOX)

static void okButtonClicked(GtkButton*, WebKitAuthenticationDialog* authDialog)
{
    WebKitAuthenticationDialogPrivate* priv = authDialog->priv;
    WebKitCredential* credential = webkitCredentialCreate(webkitAuthenticationWidgetCreateCredential(WEBKIT_AUTHENTICATION_WIDGET(priv->authWidget)));
    webkit_authentication_request_authenticate(priv->request.get(), credential);
    webkit_credential_free(credential);
    gtk_widget_destroy(GTK_WIDGET(authDialog));
}

static void cancelButtonClicked(GtkButton*, WebKitAuthenticationDialog* authDialog)
{
    webkit_authentication_request_authenticate(authDialog->priv->request.get(), 0);
    gtk_widget_destroy(GTK_WIDGET(authDialog));
}

static void pageLoadFailed(WebKitWebView*, WebKitLoadEvent, const char*, GError*, WebKitAuthenticationDialog* authDialog)
{
    webkit_authentication_request_cancel(authDialog->priv->request.get());
    gtk_widget_destroy(GTK_WIDGET(authDialog));
}

static void webkitAuthenticationDialogInitialize(WebKitAuthenticationDialog* authDialog, CredentialStorageMode credentialStorageMode, WebKitWebView* webView)
{
    GtkWidget* frame = gtk_frame_new(0);
    gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);

    GtkWidget* vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_set_border_width(GTK_CONTAINER(vBox), 5);

    GtkWidget* buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(buttonBox), GTK_BUTTONBOX_END);
    gtk_container_set_border_width(GTK_CONTAINER(buttonBox), 5);
    gtk_box_set_spacing(GTK_BOX(buttonBox), 6);

    GtkWidget* button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    g_signal_connect(button, "clicked", G_CALLBACK(cancelButtonClicked), authDialog);
    gtk_box_pack_end(GTK_BOX(buttonBox), button, FALSE, TRUE, 0);
    gtk_widget_show(button);

    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    authDialog->priv->defaultButton = button;
    g_signal_connect(button, "clicked", G_CALLBACK(okButtonClicked), authDialog);
    gtk_widget_set_can_default(button, TRUE);
    gtk_box_pack_end(GTK_BOX(buttonBox), button, FALSE, TRUE, 0);
    gtk_widget_show(button);

    authDialog->priv->authWidget = webkitAuthenticationWidgetNew(webkitAuthenticationRequestGetAuthenticationChallenge(authDialog->priv->request.get())->core(), credentialStorageMode);
    gtk_box_pack_start(GTK_BOX(vBox), authDialog->priv->authWidget, TRUE, TRUE, 0);
    gtk_widget_show(authDialog->priv->authWidget);

    gtk_box_pack_end(GTK_BOX(vBox), buttonBox, FALSE, TRUE, 0);
    gtk_widget_show(buttonBox);

    gtk_container_add(GTK_CONTAINER(frame), vBox);
    gtk_widget_show(vBox);

    gtk_container_add(GTK_CONTAINER(authDialog), frame);
    gtk_widget_show(frame);

    authDialog->priv->webView = webView;
    authDialog->priv->loadFailedEventID = g_signal_connect(webView, "load-failed", G_CALLBACK(pageLoadFailed), authDialog);
}

static gboolean webkitAuthenticationDialogDraw(GtkWidget* widget, cairo_t* cr)
{
    WebKitAuthenticationDialogPrivate* priv = WEBKIT_AUTHENTICATION_DIALOG(widget)->priv;

    gtk_style_context_save(priv->styleContext.get());
    gtk_style_context_add_class(priv->styleContext.get(), GTK_STYLE_CLASS_BACKGROUND);
    gtk_render_background(priv->styleContext.get(), cr, 0, 0, gtk_widget_get_allocated_width(widget), gtk_widget_get_allocated_height(widget));
    gtk_style_context_restore(priv->styleContext.get());

    GTK_WIDGET_CLASS(webkit_authentication_dialog_parent_class)->draw(widget, cr);

    return FALSE;
}

static void webkitAuthenticationDialogMap(GtkWidget* widget)
{
    WebKitAuthenticationDialogPrivate* priv = WEBKIT_AUTHENTICATION_DIALOG(widget)->priv;
    gtk_widget_grab_default(priv->defaultButton);

    GTK_WIDGET_CLASS(webkit_authentication_dialog_parent_class)->map(widget);
}

static void webkitAuthenticationDialogConstructed(GObject* object)
{
    G_OBJECT_CLASS(webkit_authentication_dialog_parent_class)->constructed(object);

    WebKitAuthenticationDialogPrivate* priv = WEBKIT_AUTHENTICATION_DIALOG(object)->priv;
    priv->styleContext = adoptGRef(gtk_style_context_new());
    GtkWidgetPath* path = gtk_widget_path_new();
    gtk_widget_path_append_type(path, GTK_TYPE_WINDOW);
    gtk_style_context_set_path(priv->styleContext.get(), path);
    gtk_widget_path_free(path);
}

static void webkitAuthenticationDialogDispose(GObject* object)
{
    WebKitAuthenticationDialogPrivate* priv = WEBKIT_AUTHENTICATION_DIALOG(object)->priv;
    if (priv->loadFailedEventID) {
        g_signal_handler_disconnect(priv->webView, priv->loadFailedEventID);
        priv->loadFailedEventID = 0;
    }

    G_OBJECT_CLASS(webkit_authentication_dialog_parent_class)->dispose(object);
}

static void webkit_authentication_dialog_class_init(WebKitAuthenticationDialogClass* klass)
{
    GObjectClass* objectClass = G_OBJECT_CLASS(klass);
    objectClass->constructed = webkitAuthenticationDialogConstructed;
    objectClass->dispose = webkitAuthenticationDialogDispose;

    GtkWidgetClass* widgetClass = GTK_WIDGET_CLASS(klass);
    widgetClass->draw = webkitAuthenticationDialogDraw;
    widgetClass->map = webkitAuthenticationDialogMap;
}

GtkWidget* webkitAuthenticationDialogNew(WebKitAuthenticationRequest* request, CredentialStorageMode mode, WebKitWebView* webView)
{
    WebKitAuthenticationDialog* authDialog = WEBKIT_AUTHENTICATION_DIALOG(g_object_new(WEBKIT_TYPE_AUTHENTICATION_DIALOG, NULL));
    authDialog->priv->request = request;
    webkitAuthenticationDialogInitialize(authDialog, mode, webView);
    return GTK_WIDGET(authDialog);
}