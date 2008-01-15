#ifndef PULSE_AUDIO_THREAD
#include <QObject>
#include <QTimer>
#include <QThread>
#include <QString>

#include <QHash>

extern "C"
{
#include <pulse/introspect.h>
#include <pulse/pulseaudio.h>
#include <pulse/browser.h>
}

class projectM;


class QPulseAudioThread : public QThread
{	
	Q_OBJECT
	public:
		//typedef QMap<int, QString> SourceContainer;
		typedef QHash<int, QString> SourceContainer;
		QPulseAudioThread () {}
		QPulseAudioThread(int _argc, char **_argv, projectM * projectM, QObject *parent);
		virtual ~QPulseAudioThread() ;
		void run();
		void cleanup();

		inline const SourceContainer & SourceList() {
			return sourceList;
		}

	public slots:
		inline void insertSource(int index, const QString & name) {
			sourceList[index]= name;
		}

		void connectSource(int index);
	private:
		static void pulseQuit ( int ret );
		static void stream_read_callback ( pa_stream *s, size_t length, void *userdata );
		static void stream_state_callback ( pa_stream *s, void *userdata );
		static void context_state_callback ( pa_context *c, void *userdata );
		static void initialize_callbacks ( QPulseAudioThread * pulseThread );
		static void context_drain_complete ( pa_context*c, void *userdata );
		static void stream_drain_complete ( pa_stream*s, int success, void *userdata );
		static void stdout_callback ( pa_mainloop_api*a, pa_io_event *e, int fd, pa_io_event_flags_t f, void *userdata );
		static void exit_signal_callback ( pa_mainloop_api*m, pa_signal_event *e, int sig, void *userdata );
		 static void stream_update_timing_callback ( pa_stream *s, int success, void *userdata );
		 static void sigusr1_signal_callback ( pa_mainloop_api*m, pa_signal_event *e, int sig, void *userdata );
		static void pa_source_info_callback ( pa_context *c, const pa_source_info *i, int eol, void *userdata );
		 static void subscribe_callback ( struct pa_context *c, enum pa_subscription_event_type t, uint32_t index, void *userdata );
		static void time_event_callback ( pa_mainloop_api*m, pa_time_event *e, const struct timeval *tv, void *userdata );
		

		static SourceContainer sourceList;
		int sourceIndex;
		int argc;
		char ** argv;
		projectM * m_projectM;

};
#endif