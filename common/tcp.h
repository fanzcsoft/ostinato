#ifndef _TCP_H
#define _TCP_H

#include "abstractprotocol.h"

#include "tcp.pb.h"
#include "ui_tcp.h"

#define TCP_FLAG_URG	0x20
#define TCP_FLAG_ACK	0x10
#define TCP_FLAG_PSH	0x08
#define TCP_FLAG_RST	0x04
#define TCP_FLAG_SYN	0x02
#define TCP_FLAG_FIN	0x01

class TcpConfigForm : public QWidget, public Ui::tcp
{
	Q_OBJECT
public:
	TcpConfigForm(QWidget *parent = 0);
};

class TcpProtocol : public AbstractProtocol
{
private:
	OstProto::Tcp	data;
	TcpConfigForm	*configForm;
	enum tcpfield
	{
		tcp_src_port = 0,
		tcp_dst_port,
		tcp_seq_num,
		tcp_ack_num,
		tcp_hdrlen,
		tcp_rsvd,
		tcp_flags,
		tcp_window,
		tcp_cksum,
		tcp_urg_ptr,

		tcp_is_override_hdrlen,
		tcp_is_override_cksum,

		tcp_fieldCount
	};

public:
	TcpProtocol(StreamBase *stream, AbstractProtocol *parent = 0);
	virtual ~TcpProtocol();

	static AbstractProtocol* createInstance(StreamBase *stream,
		AbstractProtocol *parent = 0);
	virtual quint32 protocolNumber() const;

	virtual void protoDataCopyInto(OstProto::Protocol &protocol) const;
	virtual void protoDataCopyFrom(const OstProto::Protocol &protocol);

	virtual QString name() const;
	virtual QString shortName() const;
	virtual quint32 protocolId(ProtocolIdType type) const;

	virtual int	fieldCount() const;

	virtual AbstractProtocol::FieldFlags fieldFlags(int index) const;
	virtual QVariant fieldData(int index, FieldAttrib attrib,
		   	int streamIndex = 0) const;
	virtual bool setFieldData(int index, const QVariant &value, 
			FieldAttrib attrib = FieldValue);

	virtual QWidget* configWidget();
	virtual void loadConfigWidget();
	virtual void storeConfigWidget();
};

#endif