#ifndef JAMTEMPLATE_AUDIO_IMPL_HPP
#define JAMTEMPLATE_AUDIO_IMPL_HPP

#include <audio/audio_interface.hpp>
#include <oalpp/sound_context.hpp>
#include <map>
#include <vector>

namespace jt {
class AudioImpl : public AudioInterface {
public:
    ~AudioImpl();

    void update() override;

    std::shared_ptr<jt::SoundInterface> addTemporarySound(std::string const& fileName) override;

    std::shared_ptr<jt::SoundInterface> addPermanentSound(
        std::string const& identifier, std::string const& fileName) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& fileName, oalpp::effects::MonoEffectInterface& effect) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& introFileName, std::string const& loopingFileName,
        oalpp::effects::MonoEffectInterface& effect) override;

    std::shared_ptr<jt::SoundInterface> soundPool(
        std::string const& baseIdentifier, std::string const& fileName, std::size_t count) override;

    std::shared_ptr<jt::SoundInterface> getPermanentSound(std::string const& identifier) override;

    void removePermanentSound(std::string const& identifier) override;

    oalpp::SoundContextInterface& getContext() override;

private:
    oalpp::SoundContext m_context;

    std::vector<std::weak_ptr<jt::SoundInterface>> m_temporarySounds {};
    std::map<std::string, std::shared_ptr<jt::SoundInterface>> m_permanentSounds {};

    void cleanUpUnusedSounds();
};
} // namespace jt

#endif // JAMTEMPLATE_AUDIO_IMPL_HPP
