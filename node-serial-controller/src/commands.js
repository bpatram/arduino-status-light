/*eslint-disable block-scoped-var, no-redeclare, no-control-regex, no-prototype-builtins*/
import * as $protobuf from "protobufjs/minimal";

// Common aliases
const $Reader = $protobuf.Reader, $Writer = $protobuf.Writer, $util = $protobuf.util;

// Exported root namespace
const $root = $protobuf.roots["default"] || ($protobuf.roots["default"] = {});

/**
 * Relay enum.
 * @exports Relay
 * @enum {string}
 * @property {number} ALL=0 ALL value
 * @property {number} ONE=1 ONE value
 * @property {number} TWO=2 TWO value
 * @property {number} THREE=3 THREE value
 * @property {number} FOUR=4 FOUR value
 */
$root.Relay = (function() {
    const valuesById = {}, values = Object.create(valuesById);
    values[valuesById[0] = "ALL"] = 0;
    values[valuesById[1] = "ONE"] = 1;
    values[valuesById[2] = "TWO"] = 2;
    values[valuesById[3] = "THREE"] = 3;
    values[valuesById[4] = "FOUR"] = 4;
    return values;
})();

export const StatusResponse = $root.StatusResponse = (() => {

    /**
     * Properties of a StatusResponse.
     * @exports IStatusResponse
     * @interface IStatusResponse
     * @property {StatusResponse.IStatus} relayOne StatusResponse relayOne
     * @property {StatusResponse.IStatus} relayTwo StatusResponse relayTwo
     * @property {StatusResponse.IStatus} relayThree StatusResponse relayThree
     * @property {StatusResponse.IStatus} relayFour StatusResponse relayFour
     */

    /**
     * Constructs a new StatusResponse.
     * @exports StatusResponse
     * @classdesc Represents a StatusResponse.
     * @implements IStatusResponse
     * @constructor
     * @param {IStatusResponse=} [properties] Properties to set
     */
    function StatusResponse(properties) {
        if (properties)
            for (let keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                if (properties[keys[i]] != null)
                    this[keys[i]] = properties[keys[i]];
    }

    /**
     * StatusResponse relayOne.
     * @member {StatusResponse.IStatus} relayOne
     * @memberof StatusResponse
     * @instance
     */
    StatusResponse.prototype.relayOne = null;

    /**
     * StatusResponse relayTwo.
     * @member {StatusResponse.IStatus} relayTwo
     * @memberof StatusResponse
     * @instance
     */
    StatusResponse.prototype.relayTwo = null;

    /**
     * StatusResponse relayThree.
     * @member {StatusResponse.IStatus} relayThree
     * @memberof StatusResponse
     * @instance
     */
    StatusResponse.prototype.relayThree = null;

    /**
     * StatusResponse relayFour.
     * @member {StatusResponse.IStatus} relayFour
     * @memberof StatusResponse
     * @instance
     */
    StatusResponse.prototype.relayFour = null;

    /**
     * Creates a new StatusResponse instance using the specified properties.
     * @function create
     * @memberof StatusResponse
     * @static
     * @param {IStatusResponse=} [properties] Properties to set
     * @returns {StatusResponse} StatusResponse instance
     */
    StatusResponse.create = function create(properties) {
        return new StatusResponse(properties);
    };

    /**
     * Encodes the specified StatusResponse message. Does not implicitly {@link StatusResponse.verify|verify} messages.
     * @function encode
     * @memberof StatusResponse
     * @static
     * @param {IStatusResponse} message StatusResponse message or plain object to encode
     * @param {$protobuf.Writer} [writer] Writer to encode to
     * @returns {$protobuf.Writer} Writer
     */
    StatusResponse.encode = function encode(message, writer) {
        if (!writer)
            writer = $Writer.create();
        $root.StatusResponse.Status.encode(message.relayOne, writer.uint32(/* id 1, wireType 2 =*/10).fork()).ldelim();
        $root.StatusResponse.Status.encode(message.relayTwo, writer.uint32(/* id 2, wireType 2 =*/18).fork()).ldelim();
        $root.StatusResponse.Status.encode(message.relayThree, writer.uint32(/* id 3, wireType 2 =*/26).fork()).ldelim();
        $root.StatusResponse.Status.encode(message.relayFour, writer.uint32(/* id 4, wireType 2 =*/34).fork()).ldelim();
        return writer;
    };

    /**
     * Encodes the specified StatusResponse message, length delimited. Does not implicitly {@link StatusResponse.verify|verify} messages.
     * @function encodeDelimited
     * @memberof StatusResponse
     * @static
     * @param {IStatusResponse} message StatusResponse message or plain object to encode
     * @param {$protobuf.Writer} [writer] Writer to encode to
     * @returns {$protobuf.Writer} Writer
     */
    StatusResponse.encodeDelimited = function encodeDelimited(message, writer) {
        return this.encode(message, writer).ldelim();
    };

    /**
     * Decodes a StatusResponse message from the specified reader or buffer.
     * @function decode
     * @memberof StatusResponse
     * @static
     * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
     * @param {number} [length] Message length if known beforehand
     * @returns {StatusResponse} StatusResponse
     * @throws {Error} If the payload is not a reader or valid buffer
     * @throws {$protobuf.util.ProtocolError} If required fields are missing
     */
    StatusResponse.decode = function decode(reader, length) {
        if (!(reader instanceof $Reader))
            reader = $Reader.create(reader);
        let end = length === undefined ? reader.len : reader.pos + length, message = new $root.StatusResponse();
        while (reader.pos < end) {
            let tag = reader.uint32();
            switch (tag >>> 3) {
            case 1:
                message.relayOne = $root.StatusResponse.Status.decode(reader, reader.uint32());
                break;
            case 2:
                message.relayTwo = $root.StatusResponse.Status.decode(reader, reader.uint32());
                break;
            case 3:
                message.relayThree = $root.StatusResponse.Status.decode(reader, reader.uint32());
                break;
            case 4:
                message.relayFour = $root.StatusResponse.Status.decode(reader, reader.uint32());
                break;
            default:
                reader.skipType(tag & 7);
                break;
            }
        }
        if (!message.hasOwnProperty("relayOne"))
            throw $util.ProtocolError("missing required 'relayOne'", { instance: message });
        if (!message.hasOwnProperty("relayTwo"))
            throw $util.ProtocolError("missing required 'relayTwo'", { instance: message });
        if (!message.hasOwnProperty("relayThree"))
            throw $util.ProtocolError("missing required 'relayThree'", { instance: message });
        if (!message.hasOwnProperty("relayFour"))
            throw $util.ProtocolError("missing required 'relayFour'", { instance: message });
        return message;
    };

    /**
     * Decodes a StatusResponse message from the specified reader or buffer, length delimited.
     * @function decodeDelimited
     * @memberof StatusResponse
     * @static
     * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
     * @returns {StatusResponse} StatusResponse
     * @throws {Error} If the payload is not a reader or valid buffer
     * @throws {$protobuf.util.ProtocolError} If required fields are missing
     */
    StatusResponse.decodeDelimited = function decodeDelimited(reader) {
        if (!(reader instanceof $Reader))
            reader = new $Reader(reader);
        return this.decode(reader, reader.uint32());
    };

    /**
     * Verifies a StatusResponse message.
     * @function verify
     * @memberof StatusResponse
     * @static
     * @param {Object.<string,*>} message Plain object to verify
     * @returns {string|null} `null` if valid, otherwise the reason why it is not
     */
    StatusResponse.verify = function verify(message) {
        if (typeof message !== "object" || message === null)
            return "object expected";
        {
            let error = $root.StatusResponse.Status.verify(message.relayOne);
            if (error)
                return "relayOne." + error;
        }
        {
            let error = $root.StatusResponse.Status.verify(message.relayTwo);
            if (error)
                return "relayTwo." + error;
        }
        {
            let error = $root.StatusResponse.Status.verify(message.relayThree);
            if (error)
                return "relayThree." + error;
        }
        {
            let error = $root.StatusResponse.Status.verify(message.relayFour);
            if (error)
                return "relayFour." + error;
        }
        return null;
    };

    /**
     * Creates a StatusResponse message from a plain object. Also converts values to their respective internal types.
     * @function fromObject
     * @memberof StatusResponse
     * @static
     * @param {Object.<string,*>} object Plain object
     * @returns {StatusResponse} StatusResponse
     */
    StatusResponse.fromObject = function fromObject(object) {
        if (object instanceof $root.StatusResponse)
            return object;
        let message = new $root.StatusResponse();
        if (object.relayOne != null) {
            if (typeof object.relayOne !== "object")
                throw TypeError(".StatusResponse.relayOne: object expected");
            message.relayOne = $root.StatusResponse.Status.fromObject(object.relayOne);
        }
        if (object.relayTwo != null) {
            if (typeof object.relayTwo !== "object")
                throw TypeError(".StatusResponse.relayTwo: object expected");
            message.relayTwo = $root.StatusResponse.Status.fromObject(object.relayTwo);
        }
        if (object.relayThree != null) {
            if (typeof object.relayThree !== "object")
                throw TypeError(".StatusResponse.relayThree: object expected");
            message.relayThree = $root.StatusResponse.Status.fromObject(object.relayThree);
        }
        if (object.relayFour != null) {
            if (typeof object.relayFour !== "object")
                throw TypeError(".StatusResponse.relayFour: object expected");
            message.relayFour = $root.StatusResponse.Status.fromObject(object.relayFour);
        }
        return message;
    };

    /**
     * Creates a plain object from a StatusResponse message. Also converts values to other types if specified.
     * @function toObject
     * @memberof StatusResponse
     * @static
     * @param {StatusResponse} message StatusResponse
     * @param {$protobuf.IConversionOptions} [options] Conversion options
     * @returns {Object.<string,*>} Plain object
     */
    StatusResponse.toObject = function toObject(message, options) {
        if (!options)
            options = {};
        let object = {};
        if (options.defaults) {
            object.relayOne = null;
            object.relayTwo = null;
            object.relayThree = null;
            object.relayFour = null;
        }
        if (message.relayOne != null && message.hasOwnProperty("relayOne"))
            object.relayOne = $root.StatusResponse.Status.toObject(message.relayOne, options);
        if (message.relayTwo != null && message.hasOwnProperty("relayTwo"))
            object.relayTwo = $root.StatusResponse.Status.toObject(message.relayTwo, options);
        if (message.relayThree != null && message.hasOwnProperty("relayThree"))
            object.relayThree = $root.StatusResponse.Status.toObject(message.relayThree, options);
        if (message.relayFour != null && message.hasOwnProperty("relayFour"))
            object.relayFour = $root.StatusResponse.Status.toObject(message.relayFour, options);
        return object;
    };

    /**
     * Converts this StatusResponse to JSON.
     * @function toJSON
     * @memberof StatusResponse
     * @instance
     * @returns {Object.<string,*>} JSON object
     */
    StatusResponse.prototype.toJSON = function toJSON() {
        return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
    };

    /**
     * State enum.
     * @name StatusResponse.State
     * @enum {string}
     * @property {number} OFF=0 OFF value
     * @property {number} ON=1 ON value
     */
    StatusResponse.State = (function() {
        const valuesById = {}, values = Object.create(valuesById);
        values[valuesById[0] = "OFF"] = 0;
        values[valuesById[1] = "ON"] = 1;
        return values;
    })();

    StatusResponse.Status = (function() {

        /**
         * Properties of a Status.
         * @memberof StatusResponse
         * @interface IStatus
         * @property {Relay} relay Status relay
         * @property {StatusResponse.State} state Status state
         */

        /**
         * Constructs a new Status.
         * @memberof StatusResponse
         * @classdesc Represents a Status.
         * @implements IStatus
         * @constructor
         * @param {StatusResponse.IStatus=} [properties] Properties to set
         */
        function Status(properties) {
            if (properties)
                for (let keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * Status relay.
         * @member {Relay} relay
         * @memberof StatusResponse.Status
         * @instance
         */
        Status.prototype.relay = 0;

        /**
         * Status state.
         * @member {StatusResponse.State} state
         * @memberof StatusResponse.Status
         * @instance
         */
        Status.prototype.state = 0;

        /**
         * Creates a new Status instance using the specified properties.
         * @function create
         * @memberof StatusResponse.Status
         * @static
         * @param {StatusResponse.IStatus=} [properties] Properties to set
         * @returns {StatusResponse.Status} Status instance
         */
        Status.create = function create(properties) {
            return new Status(properties);
        };

        /**
         * Encodes the specified Status message. Does not implicitly {@link StatusResponse.Status.verify|verify} messages.
         * @function encode
         * @memberof StatusResponse.Status
         * @static
         * @param {StatusResponse.IStatus} message Status message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        Status.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.relay);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.state);
            return writer;
        };

        /**
         * Encodes the specified Status message, length delimited. Does not implicitly {@link StatusResponse.Status.verify|verify} messages.
         * @function encodeDelimited
         * @memberof StatusResponse.Status
         * @static
         * @param {StatusResponse.IStatus} message Status message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        Status.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a Status message from the specified reader or buffer.
         * @function decode
         * @memberof StatusResponse.Status
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {StatusResponse.Status} Status
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        Status.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            let end = length === undefined ? reader.len : reader.pos + length, message = new $root.StatusResponse.Status();
            while (reader.pos < end) {
                let tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.relay = reader.int32();
                    break;
                case 2:
                    message.state = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("relay"))
                throw $util.ProtocolError("missing required 'relay'", { instance: message });
            if (!message.hasOwnProperty("state"))
                throw $util.ProtocolError("missing required 'state'", { instance: message });
            return message;
        };

        /**
         * Decodes a Status message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof StatusResponse.Status
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {StatusResponse.Status} Status
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        Status.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a Status message.
         * @function verify
         * @memberof StatusResponse.Status
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        Status.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            switch (message.relay) {
            default:
                return "relay: enum value expected";
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                break;
            }
            switch (message.state) {
            default:
                return "state: enum value expected";
            case 0:
            case 1:
                break;
            }
            return null;
        };

        /**
         * Creates a Status message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof StatusResponse.Status
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {StatusResponse.Status} Status
         */
        Status.fromObject = function fromObject(object) {
            if (object instanceof $root.StatusResponse.Status)
                return object;
            let message = new $root.StatusResponse.Status();
            switch (object.relay) {
            case "ALL":
            case 0:
                message.relay = 0;
                break;
            case "ONE":
            case 1:
                message.relay = 1;
                break;
            case "TWO":
            case 2:
                message.relay = 2;
                break;
            case "THREE":
            case 3:
                message.relay = 3;
                break;
            case "FOUR":
            case 4:
                message.relay = 4;
                break;
            }
            switch (object.state) {
            case "OFF":
            case 0:
                message.state = 0;
                break;
            case "ON":
            case 1:
                message.state = 1;
                break;
            }
            return message;
        };

        /**
         * Creates a plain object from a Status message. Also converts values to other types if specified.
         * @function toObject
         * @memberof StatusResponse.Status
         * @static
         * @param {StatusResponse.Status} message Status
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        Status.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            let object = {};
            if (options.defaults) {
                object.relay = options.enums === String ? "ALL" : 0;
                object.state = options.enums === String ? "OFF" : 0;
            }
            if (message.relay != null && message.hasOwnProperty("relay"))
                object.relay = options.enums === String ? $root.Relay[message.relay] : message.relay;
            if (message.state != null && message.hasOwnProperty("state"))
                object.state = options.enums === String ? $root.StatusResponse.State[message.state] : message.state;
            return object;
        };

        /**
         * Converts this Status to JSON.
         * @function toJSON
         * @memberof StatusResponse.Status
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        Status.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return Status;
    })();

    return StatusResponse;
})();

export const CommandRequest = $root.CommandRequest = (() => {

    /**
     * Properties of a CommandRequest.
     * @exports ICommandRequest
     * @interface ICommandRequest
     * @property {CommandRequest.Command} command CommandRequest command
     * @property {Relay|null} [relay] CommandRequest relay
     * @property {number|null} [iterations] CommandRequest iterations
     * @property {number|null} [onMillis] CommandRequest onMillis
     * @property {number|null} [offMillis] CommandRequest offMillis
     * @property {number|null} [pauseMillis] CommandRequest pauseMillis
     */

    /**
     * Constructs a new CommandRequest.
     * @exports CommandRequest
     * @classdesc Represents a CommandRequest.
     * @implements ICommandRequest
     * @constructor
     * @param {ICommandRequest=} [properties] Properties to set
     */
    function CommandRequest(properties) {
        if (properties)
            for (let keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                if (properties[keys[i]] != null)
                    this[keys[i]] = properties[keys[i]];
    }

    /**
     * CommandRequest command.
     * @member {CommandRequest.Command} command
     * @memberof CommandRequest
     * @instance
     */
    CommandRequest.prototype.command = 0;

    /**
     * CommandRequest relay.
     * @member {Relay} relay
     * @memberof CommandRequest
     * @instance
     */
    CommandRequest.prototype.relay = 0;

    /**
     * CommandRequest iterations.
     * @member {number} iterations
     * @memberof CommandRequest
     * @instance
     */
    CommandRequest.prototype.iterations = 1;

    /**
     * CommandRequest onMillis.
     * @member {number} onMillis
     * @memberof CommandRequest
     * @instance
     */
    CommandRequest.prototype.onMillis = 500;

    /**
     * CommandRequest offMillis.
     * @member {number} offMillis
     * @memberof CommandRequest
     * @instance
     */
    CommandRequest.prototype.offMillis = 500;

    /**
     * CommandRequest pauseMillis.
     * @member {number} pauseMillis
     * @memberof CommandRequest
     * @instance
     */
    CommandRequest.prototype.pauseMillis = 0;

    /**
     * Creates a new CommandRequest instance using the specified properties.
     * @function create
     * @memberof CommandRequest
     * @static
     * @param {ICommandRequest=} [properties] Properties to set
     * @returns {CommandRequest} CommandRequest instance
     */
    CommandRequest.create = function create(properties) {
        return new CommandRequest(properties);
    };

    /**
     * Encodes the specified CommandRequest message. Does not implicitly {@link CommandRequest.verify|verify} messages.
     * @function encode
     * @memberof CommandRequest
     * @static
     * @param {ICommandRequest} message CommandRequest message or plain object to encode
     * @param {$protobuf.Writer} [writer] Writer to encode to
     * @returns {$protobuf.Writer} Writer
     */
    CommandRequest.encode = function encode(message, writer) {
        if (!writer)
            writer = $Writer.create();
        writer.uint32(/* id 1, wireType 0 =*/8).int32(message.command);
        if (message.relay != null && message.hasOwnProperty("relay"))
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.relay);
        if (message.iterations != null && message.hasOwnProperty("iterations"))
            writer.uint32(/* id 3, wireType 0 =*/24).int32(message.iterations);
        if (message.onMillis != null && message.hasOwnProperty("onMillis"))
            writer.uint32(/* id 4, wireType 0 =*/32).int32(message.onMillis);
        if (message.offMillis != null && message.hasOwnProperty("offMillis"))
            writer.uint32(/* id 5, wireType 0 =*/40).int32(message.offMillis);
        if (message.pauseMillis != null && message.hasOwnProperty("pauseMillis"))
            writer.uint32(/* id 6, wireType 0 =*/48).int32(message.pauseMillis);
        return writer;
    };

    /**
     * Encodes the specified CommandRequest message, length delimited. Does not implicitly {@link CommandRequest.verify|verify} messages.
     * @function encodeDelimited
     * @memberof CommandRequest
     * @static
     * @param {ICommandRequest} message CommandRequest message or plain object to encode
     * @param {$protobuf.Writer} [writer] Writer to encode to
     * @returns {$protobuf.Writer} Writer
     */
    CommandRequest.encodeDelimited = function encodeDelimited(message, writer) {
        return this.encode(message, writer).ldelim();
    };

    /**
     * Decodes a CommandRequest message from the specified reader or buffer.
     * @function decode
     * @memberof CommandRequest
     * @static
     * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
     * @param {number} [length] Message length if known beforehand
     * @returns {CommandRequest} CommandRequest
     * @throws {Error} If the payload is not a reader or valid buffer
     * @throws {$protobuf.util.ProtocolError} If required fields are missing
     */
    CommandRequest.decode = function decode(reader, length) {
        if (!(reader instanceof $Reader))
            reader = $Reader.create(reader);
        let end = length === undefined ? reader.len : reader.pos + length, message = new $root.CommandRequest();
        while (reader.pos < end) {
            let tag = reader.uint32();
            switch (tag >>> 3) {
            case 1:
                message.command = reader.int32();
                break;
            case 2:
                message.relay = reader.int32();
                break;
            case 3:
                message.iterations = reader.int32();
                break;
            case 4:
                message.onMillis = reader.int32();
                break;
            case 5:
                message.offMillis = reader.int32();
                break;
            case 6:
                message.pauseMillis = reader.int32();
                break;
            default:
                reader.skipType(tag & 7);
                break;
            }
        }
        if (!message.hasOwnProperty("command"))
            throw $util.ProtocolError("missing required 'command'", { instance: message });
        return message;
    };

    /**
     * Decodes a CommandRequest message from the specified reader or buffer, length delimited.
     * @function decodeDelimited
     * @memberof CommandRequest
     * @static
     * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
     * @returns {CommandRequest} CommandRequest
     * @throws {Error} If the payload is not a reader or valid buffer
     * @throws {$protobuf.util.ProtocolError} If required fields are missing
     */
    CommandRequest.decodeDelimited = function decodeDelimited(reader) {
        if (!(reader instanceof $Reader))
            reader = new $Reader(reader);
        return this.decode(reader, reader.uint32());
    };

    /**
     * Verifies a CommandRequest message.
     * @function verify
     * @memberof CommandRequest
     * @static
     * @param {Object.<string,*>} message Plain object to verify
     * @returns {string|null} `null` if valid, otherwise the reason why it is not
     */
    CommandRequest.verify = function verify(message) {
        if (typeof message !== "object" || message === null)
            return "object expected";
        switch (message.command) {
        default:
            return "command: enum value expected";
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        }
        if (message.relay != null && message.hasOwnProperty("relay"))
            switch (message.relay) {
            default:
                return "relay: enum value expected";
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                break;
            }
        if (message.iterations != null && message.hasOwnProperty("iterations"))
            if (!$util.isInteger(message.iterations))
                return "iterations: integer expected";
        if (message.onMillis != null && message.hasOwnProperty("onMillis"))
            if (!$util.isInteger(message.onMillis))
                return "onMillis: integer expected";
        if (message.offMillis != null && message.hasOwnProperty("offMillis"))
            if (!$util.isInteger(message.offMillis))
                return "offMillis: integer expected";
        if (message.pauseMillis != null && message.hasOwnProperty("pauseMillis"))
            if (!$util.isInteger(message.pauseMillis))
                return "pauseMillis: integer expected";
        return null;
    };

    /**
     * Creates a CommandRequest message from a plain object. Also converts values to their respective internal types.
     * @function fromObject
     * @memberof CommandRequest
     * @static
     * @param {Object.<string,*>} object Plain object
     * @returns {CommandRequest} CommandRequest
     */
    CommandRequest.fromObject = function fromObject(object) {
        if (object instanceof $root.CommandRequest)
            return object;
        let message = new $root.CommandRequest();
        switch (object.command) {
        case "STATUS":
        case 0:
            message.command = 0;
            break;
        case "HELP":
        case 1:
            message.command = 1;
            break;
        case "ON":
        case 2:
            message.command = 2;
            break;
        case "OFF":
        case 3:
            message.command = 3;
            break;
        case "INVERT":
        case 4:
            message.command = 4;
            break;
        case "SEQUENCE":
        case 5:
            message.command = 5;
            break;
        case "FLASH":
        case 6:
            message.command = 6;
            break;
        case "DEMO":
        case 7:
            message.command = 7;
            break;
        }
        switch (object.relay) {
        case "ALL":
        case 0:
            message.relay = 0;
            break;
        case "ONE":
        case 1:
            message.relay = 1;
            break;
        case "TWO":
        case 2:
            message.relay = 2;
            break;
        case "THREE":
        case 3:
            message.relay = 3;
            break;
        case "FOUR":
        case 4:
            message.relay = 4;
            break;
        }
        if (object.iterations != null)
            message.iterations = object.iterations | 0;
        if (object.onMillis != null)
            message.onMillis = object.onMillis | 0;
        if (object.offMillis != null)
            message.offMillis = object.offMillis | 0;
        if (object.pauseMillis != null)
            message.pauseMillis = object.pauseMillis | 0;
        return message;
    };

    /**
     * Creates a plain object from a CommandRequest message. Also converts values to other types if specified.
     * @function toObject
     * @memberof CommandRequest
     * @static
     * @param {CommandRequest} message CommandRequest
     * @param {$protobuf.IConversionOptions} [options] Conversion options
     * @returns {Object.<string,*>} Plain object
     */
    CommandRequest.toObject = function toObject(message, options) {
        if (!options)
            options = {};
        let object = {};
        if (options.defaults) {
            object.command = options.enums === String ? "STATUS" : 0;
            object.relay = options.enums === String ? "ALL" : 0;
            object.iterations = 1;
            object.onMillis = 500;
            object.offMillis = 500;
            object.pauseMillis = 0;
        }
        if (message.command != null && message.hasOwnProperty("command"))
            object.command = options.enums === String ? $root.CommandRequest.Command[message.command] : message.command;
        if (message.relay != null && message.hasOwnProperty("relay"))
            object.relay = options.enums === String ? $root.Relay[message.relay] : message.relay;
        if (message.iterations != null && message.hasOwnProperty("iterations"))
            object.iterations = message.iterations;
        if (message.onMillis != null && message.hasOwnProperty("onMillis"))
            object.onMillis = message.onMillis;
        if (message.offMillis != null && message.hasOwnProperty("offMillis"))
            object.offMillis = message.offMillis;
        if (message.pauseMillis != null && message.hasOwnProperty("pauseMillis"))
            object.pauseMillis = message.pauseMillis;
        return object;
    };

    /**
     * Converts this CommandRequest to JSON.
     * @function toJSON
     * @memberof CommandRequest
     * @instance
     * @returns {Object.<string,*>} JSON object
     */
    CommandRequest.prototype.toJSON = function toJSON() {
        return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
    };

    /**
     * Command enum.
     * @name CommandRequest.Command
     * @enum {string}
     * @property {number} STATUS=0 STATUS value
     * @property {number} HELP=1 HELP value
     * @property {number} ON=2 ON value
     * @property {number} OFF=3 OFF value
     * @property {number} INVERT=4 INVERT value
     * @property {number} SEQUENCE=5 SEQUENCE value
     * @property {number} FLASH=6 FLASH value
     * @property {number} DEMO=7 DEMO value
     */
    CommandRequest.Command = (function() {
        const valuesById = {}, values = Object.create(valuesById);
        values[valuesById[0] = "STATUS"] = 0;
        values[valuesById[1] = "HELP"] = 1;
        values[valuesById[2] = "ON"] = 2;
        values[valuesById[3] = "OFF"] = 3;
        values[valuesById[4] = "INVERT"] = 4;
        values[valuesById[5] = "SEQUENCE"] = 5;
        values[valuesById[6] = "FLASH"] = 6;
        values[valuesById[7] = "DEMO"] = 7;
        return values;
    })();

    return CommandRequest;
})();

export { $root as default };
