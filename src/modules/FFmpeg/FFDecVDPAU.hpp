/*
    QMPlay2 is a video and audio player.
    Copyright (C) 2010-2023  Błażej Szczygieł

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <FFDecHWAccel.hpp>

#include <memory>

class VDPAU;

class FFMPEG_EXPORT FFDecVDPAU final : public FFDecHWAccel
{
public:
    FFDecVDPAU(Module &);
    ~FFDecVDPAU();

    bool set() override;

    QString name() const override;

    std::shared_ptr<VideoFilter> hwAccelFilter() const override;

    int decodeVideo(const Packet &encodedPacket, Frame &decoded, AVPixelFormat &newPixFmt, bool flush, unsigned hurryUp) override;

    bool open(StreamInfo &streamInfo) override;

private:
    static void preemptionCallback(uint32_t device, void *context);

private:
    std::shared_ptr<VDPAU> m_vdpau;

    int m_deintMethod = 0;
    bool m_nrEnabled = false;
    float m_nrLevel = 0.0f;
};
