#if !defined(AT_COMMANDS)
#define AT_COMMANDS

#include <at.h>
#include <DS3231.h>

class ATPing : public at::Handler
{
public:
    ATPing() : at::Handler("AT+PING"){};
    void Handle(at::Input input, at::Responder *resp)
    {
        if (input.length == 0)
        {
            resp->writeLine("PONG");
        }
        else
        {
            resp->writeLine(input.body, input.length);
        }
        resp->writeOk();
    }
};

struct ParsedNumber
{
    const uint32_t value;
    const bool valid;

    ParsedNumber(uint32_t value, bool valid) : value(value), valid(valid){};
};

ParsedNumber parseNumber(const char *buffer, const size_t length)
{
    uint32_t result = 0;
    bool valid = true;

    for (size_t i = 0; i < length; i++)
    {
        const char digit = buffer[i];
        if (isdigit(digit) != 0)
        {
            if (i > 0)
            {
                result *= 10;
            }
            const byte value = (byte)digit - 48;
            result += value;
        }
        else
        {
            valid = false;
            break;
        }
    }

    return ParsedNumber(result, valid);
};

class ATTime : public at::Handler
{
private:
    DS3231 *_clock;
    RTClib _rtcLib;

public:
    ATTime(DS3231 *clk) : at::Handler("AT+TIME")
    {
        _clock = clk;
    };
    void Handle(at::Input input, at::Responder *resp)
    {
        if (input.length != 0)
        {
            const auto number = parseNumber(input.body, input.length);
            if (!number.valid)
            {
                resp->writeError();
                return;
            }
            const auto now = DateTime(number.value);
            _clock->enableOscillator(false, false, 3);
            _clock->setYear(now.year() - 2000); // last two digits only starting from 2k
            _clock->setMonth(now.month());
            _clock->setDate(now.day());
            _clock->setHour(now.hour());
            _clock->setMinute(now.minute());
            _clock->setSecond(now.second());
            _clock->enableOscillator(true, true, 3);
        }
        const auto now = _rtcLib.now();
        resp->write("HUMAM=");
        resp->write(now.year());
        resp->write("-");
        resp->write(now.month());
        resp->write("-");
        resp->write(now.day());
        resp->write(" ");
        resp->write(now.hour());
        resp->write(":");
        resp->write(now.minute());
        resp->write(":");
        resp->write(now.second());
        resp->writeLine("");
        resp->write("UNIX=");
        resp->write(now.unixtime());
        resp->writeLine("");
        resp->writeOk();
    }
};

#endif // AT_COMMANDS
